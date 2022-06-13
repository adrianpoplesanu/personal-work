from flask import Flask
from flask import render_template
from flask import request
from werkzeug.utils import secure_filename
app = Flask(__name__)

@app.route('/')
def graph():
    return render_template('index.html')

@app.route('/analyze-file', methods=['POST'])
def analyze_file():
    print ('analyze-file')
    file = request.files['file']
    filename = secure_filename(file.filename)
    file.save('uploads/' + filename)

    lines = open('uploads/' + filename, 'r').readlines()
    output = []
    for line in lines[1:]:
        output.append(int(line.split(',')[1].strip()))
    return str(output)
