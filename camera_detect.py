from ultralytics import YOLO
import cv2

# โหลด model ที่ train แล้ว
model = YOLO(r"C:\Users\ASUS\Desktop\NA_Project\yolo11n-cls.pt")

# เปิดกล้อง (0 = webcam, หรือใส่ path วิดีโอ)
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Predict
    results = model.predict(frame, verbose=False)
    
    # ดึงผลลัพธ์
    top1_class = results[0].names[results[0].probs.top1]
    top1_conf  = results[0].probs.top1conf.item()

    # แสดงผลบนภาพ
    label = f"{top1_class} ({top1_conf:.0%})"
    color = (0, 255, 0) if top1_class == "Healthy Leaf" else (0, 0, 255)
    cv2.putText(frame, label, (20, 40),
                cv2.FONT_HERSHEY_SIMPLEX, 1.2, color, 2)
    
    cv2.imshow("Lemon Disease Detection", frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()