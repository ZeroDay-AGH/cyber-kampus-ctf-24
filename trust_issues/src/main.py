from flask import Flask, request, jsonify, render_template, redirect, url_for, session
import jwt
import os

app = Flask(__name__)
app.secret_key = "supersecretkey"

# db
users = {"admin": os.urandom(16).hex()}

JWT_KEY = os.urandom(16).hex()

# Routes
@app.route('/')
def home():
    if 'username' in session:
        return redirect(url_for('admin'))
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            # token = jwt.encode({"username": username}, key=JWT_KEY, algorithm="HS256")   
            resp = redirect(url_for('admin'))         
            token = jwt.encode(
                {"username": username},
                JWT_KEY,
                algorithm="HS256",
                headers={"kid": "230498151c214b788dd97f22b85410a5"},
            )
            # session['token'] = token
            resp.set_cookie('token', token)
            return resp
        return render_template('error.html',error_message='Invalid credentials!'), 401
    return render_template('login.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users:
            return "User already exists!", 400
        users[username] = password
        return redirect(url_for('login'))
    return render_template('register.html')

@app.get('/admin')
def admin():
    token = request.cookies.get('token')
    if not token:
        return redirect(url_for('login'))
    try:
        payload = jwt.decode(token,options={"verify_signature": False})        
        if payload.get('username') == 'admin':
            return render_template('admin.html', users=users)
        return render_template('error.html',error_message='Unauthorized!'), 403
    except jwt.DecodeError as e:
        print(e)
        return render_template('error.html',error_message='Invalid token!'), 403

@app.route('/logout')
def logout():
    session.pop('token', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=False)
