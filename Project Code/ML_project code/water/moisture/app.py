from flask import Flask,redirect,url_for,render_template,request

app=Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/rice')
def rice():
    return render_template('rice.html')

@app.route('/prediction')
def prediction():
    return render_template('prediction.html')

@app.route('/pre', methods = ["POST"])
def pre():
    if request.method == "POST":
        n = request.form['crop']
        p = request.form['sm']
        temp = request.form['temp']
        hum =request.form['hum']
        print(p)
        if n == "rice" or p == "360 to 400" or temp == "30 to 40" or hum == "above 40" :
            return redirect(url_for("rice"))
    return render_template("rice.html")


if __name__ == '__main__':
    app.run(port=5000,debug=True)