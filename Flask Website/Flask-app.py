from flask import Flask, jsonify, render_template, request

app = Flask(__name__)

# Simulasi data sensor
sensor_data = {
    "fire_sensor": 1,  
    "mq2_sensor": 1,   
    "temperature": 25.0,  
    "humidity": 60.0      
}

notifications = []

@app.route('/')
def home():
    # Endpoint untuk halaman utama
    return render_template('index.html')

@app.route('/api/sensor_data', methods=['GET'])
def get_sensor_data(notifications=notifications):
    # Endpoint untuk mendapatkan data sensor
    #global sensor_data
    if int(sensor_data["fire_sensor"]) == 0:
        notifications.append("🔥 Api terdeteksi!")
    else:
        notifications = []
   
    if sensor_data["mq2_sensor"] == 0:
        notifications.append("⚠️ Asap terdeteksi!")

    # Kembalikan data sensor dan notifikasi
    return jsonify({
        "sensor_data": sensor_data,
        "notifications": notifications
    })

@app.route('/sensor', methods=['POST'])
def update_sensor_data():
    # global sensor_data
    data = request.get_json()
    print("Data diterima:", data)  # Log data yang diterima

    # Perbarui data sensor
    sensor_data["fire_sensor"] = data.get("fire_sensor", sensor_data["fire_sensor"])
    sensor_data["mq2_sensor"] = data.get("mq2_sensor", sensor_data["mq2_sensor"])
    sensor_data["temperature"] = data.get("temperature", sensor_data["temperature"])
    sensor_data["humidity"] = data.get("humidity", sensor_data["humidity"])

    print(sensor_data)  # Log data setelah diperbarui
    return jsonify({"status": "success", "message": "Sensor data updated!"}), 200
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
