from flask import Flask, render_template, request

app = Flask(__name__)

# Store latest sensor values
health_data = {
    'heart_rate': 0,
    'blood_pressure': '0/0',
    'temperature': 0.0
}

@app.route('/')
def dashboard():
    return render_template('dashboard.html', data=health_data)

@app.route('/update', methods=['POST'])
def update():
    data = request.json
    health_data.update(data)
    return 'Data received', 200

if __name__ == '__main__':
    app.run(debug=True)
