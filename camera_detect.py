from ultralytics import YOLO
import cv2

# Load the trained model
model = YOLO(r"runs/classify/train/weights/best.pt")

# Open the camera (0 = webcam, or provide a video file path)
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Run prediction on the current frame
    results = model.predict(frame, verbose=False)
    
    # Extract the top-1 predicted class and confidence
    top1_class = results[0].names[results[0].probs.top1]
    top1_conf  = results[0].probs.top1conf.item()

    # Display prediction result on the frame
    label = f"{top1_class} ({top1_conf:.0%})"
    HEALTHY_CLASSES = ["Healthy Leaf"] 

    # Green for healthy, red for diseased
    color = (0, 255, 0) if top1_class in HEALTHY_CLASSES else (0, 0, 255)
    cv2.putText(frame, label, (20, 40),
                cv2.FONT_HERSHEY_SIMPLEX, 1.2, color, 2)
    
    # Show the video stream with predictions
    cv2.imshow("Lemon Disease Detection", frame)
    
    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()
