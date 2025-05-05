#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "sorting_hat_model.h"  // 引入模型文件

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 设置 I2C 引脚
#define SDA_PIN 21  // SDA 对应 GPIO 21
#define SCL_PIN 22  // SCL 对应 GPIO 22

// 按钮引脚定义（P32, P33, P25, P26）
#define BUTTON1_PIN 32  // 按钮 1 对应 P32
#define BUTTON2_PIN 33  // 按钮 2 对应 P33
#define BUTTON3_PIN 25  // 按钮 3 对应 P25
#define BUTTON4_PIN 26  // 按钮 4 对应 P26

int responses[10];  // 用于存储10个问题的回答

// 创建决策树对象
Eloquent::ML::Port::DecisionTree model;

// 防抖变量
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;  // 防抖延迟（毫秒）

void setup() {
  Serial.begin(115200);

  // 初始化 OLED 显示屏
  Wire.begin(SDA_PIN, SCL_PIN);  // 使用 P21 和 P22 作为 I2C 引脚
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Sorting Hat Ready!");
  display.display();
  delay(2000);  // 显示2秒
}

int getButtonInput() {
  int reading1 = digitalRead(BUTTON1_PIN);
  int reading2 = digitalRead(BUTTON2_PIN);
  int reading3 = digitalRead(BUTTON3_PIN);
  int reading4 = digitalRead(BUTTON4_PIN);

  // 检查按钮按下后的防抖处理
  if (reading1 == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    return 1;
  }
  if (reading2 == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    return 2;
  }
  if (reading3 == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    return 3;
  }
  if (reading4 == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    return 4;
  }
  return 0;  // 如果没有按钮按下，返回0
}

void loop() {
  // 记录答案
  for (int i = 0; i < 10; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);

    // 显示问题文本和选项
    switch(i) {
      case 0:
        display.println("Question 1: Do you prefer leadership or support?");
        display.println("1: Leadership");
        display.println("2: Support");
        display.println("3: Both");
        display.println("4: Independent work");
        break;
      case 1:
        display.println("Question 2: How do you handle challenges?");
        display.println("1: Act immediately");
        display.println("2: Think carefully");
        display.println("3: Seek help");
        display.println("4: Avoid challenges");
        break;
      case 2:
        display.println("Question 3: How do you contribute in events?");
        display.println("1: Organize and plan");
        display.println("2: Take charge and perform");
        display.println("3: Help others and ensure smoothness");
        display.println("4: Prefer to stay out");
        break;
      case 3:
        display.println("Question 4: How do you deal with injustice?");
        display.println("1: Stand up and fight");
        display.println("2: Remain silent");
        display.println("3: Consult friends");
        display.println("4: Ignore it");
        break;
      case 4:
        display.println("Question 5: Do you like adventure?");
        display.println("1: Love it");
        display.println("2: Cautious but willing");
        display.println("3: Prefer team activities");
        display.println("4: Avoid adventure");
        break;
      case 5:
        display.println("Question 6: Which is more important: friendship or honor?");
        display.println("1: Friendship");
        display.println("2: Honor");
        display.println("3: Both, but I lean towards friendship");
        display.println("4: I value independence");
        break;
      case 6:
        display.println("Question 7: How do you handle pressure?");
        display.println("1: Stay calm and controlled");
        display.println("2: Seek help");
        display.println("3: Work harder to overcome");
        display.println("4: Become anxious and stressed");
        break;
      case 7:
        display.println("Question 8: Do you prefer direct action or careful thinking?");
        display.println("1: Direct action");
        display.println("2: Careful planning");
        display.println("3: Both depending on situation");
        display.println("4: I hesitate to take action");
        break;
      case 8:
        display.println("Question 9: What is your view on rules?");
        display.println("1: Must be followed");
        display.println("2: Should be flexible");
        display.println("3: Break them if needed");
        display.println("4: Avoid them");
        break;
      case 9:
        display.println("Question 10: What do you want from your House?");
        display.println("1: Adventure and challenge");
        display.println("2: Wisdom and knowledge");
        display.println("3: Friendship and loyalty");
        display.println("4: Personal achievement");
        break;
    }

    display.display();
    delay(500);  // 显示问题等待0.5秒

    // 等待按钮按下并记录
    int buttonPressed = 0;
    while (buttonPressed == 0) {
      buttonPressed = getButtonInput();  // 等待按钮按下
    }
    responses[i] = buttonPressed;

    // 显示下一个问题
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Next question...");
    display.display();
    delay(1000);  // 等待1秒进入下一个问题
  }

  // 在所有问题回答完后，使用模型进行预测
  // 注意：这里需要将数据类型转换为浮动类型，因为模型预测需要 float 类型的数组
  float responseArray[10];
  for (int i = 0; i < 10; i++) {
    responseArray[i] = (float)responses[i];
  }

  // 使用决策树模型进行预测
  int predictedHouse = model.predict(responseArray);  // 调用预测函数

  // 显示预测结果
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Your House: ");
  
  if (predictedHouse == 0) display.print("Gryffindor");
  else if (predictedHouse == 1) display.print("Slytherin");
  else if (predictedHouse == 2) display.print("Hufflepuff");
  else display.print("Ravenclaw");

  display.display();
  delay(5000);  // 显示结果5秒后重新开始
}
