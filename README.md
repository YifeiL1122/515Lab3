# 515Lab3

# Play with your sorting hat. Are all 10 questions important to create the sorting hat? If you were to remove some questions to improve user experience, which questions would you remove and justify your answer.

Not all 10 questions are crucial for the sorting hat. Some questions might not strongly differentiate between the houses, making them less important for classification.

Questions to remove:
"Which is more important: friendship or honor?"
Reason: This question is too broad and doesn’t clearly map to any house’s specific traits. Both qualities could apply to different houses, making it harder to distinguish users.

"What is your view on rules?"
Reason: This question is also quite vague. While it might differentiate between houses like Ravenclaw or Slytherin, the answers are not as distinct and might overlap across houses, making it less useful for sorting.

# If you were to improve the sorting hat, what technical improvements would you make? Consider:
How could you improve the model's accuracy or efficiency?
What additional sensors or hardware could enhance the user experience?
Does decision tree remain suitable for your choice of new sensors? If yes, carefully justify your answer. If not, what ML model would you use and explain why.

1. Improving Model Accuracy/Efficiency:
More Data: Increase dataset diversity for better generalization.

Ensemble Methods: Use Random Forests or Gradient Boosting to improve accuracy by combining decision trees.

2. Additional Sensors/Hardware:
Microphone: Voice input for a more interactive experience.

Gesture Sensors: Allow users to select answers with gestures.

Heart Rate Sensor: Capture emotional state, linking to house traits.

3. Is Decision Tree Suitable?
Not ideal for complex sensor data (voice/gesture).

Recommendation: Use Neural Networks (CNNs or RNNs), which handle high-dimensional data better and improve accuracy.
