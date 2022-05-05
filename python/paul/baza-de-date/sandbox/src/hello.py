import os
from flask import Flask, flash, request, redirect, url_for
from werkzeug.utils import secure_filename
import json


file_path = os.path.realpath(__file__)
cwd = os.getcwd()
UPLOAD_FOLDER = cwd + '/files'


app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


def transform_file_input(data):
    data = data.replace('var informatii = {', '{')
    data = data.replace('contor:', "'contor':")
    data = data.replace('cod:', "'cod':")
    data = data.replace('numepr:', "'numepr':")
    data = data.replace('prenume:', "'prenume':")
    data = data.replace('numeFata:', "'numeFata':")
    data = data.replace('nume:', "'nume':")
    data = data.replace('cale:', "'cale':")
    data = data.replace('zzn:', "'zzn':")
    data = data.replace('lln:', "'lln':")
    data = data.replace('ann:', "'ann':")
    data = data.replace('datan:', "'datan':")
    data = data.replace('datan2:', "'datan2':")
    data = data.replace('datad:', "'datad':")
    data = data.replace('varsta:', "'varsta':")
    data = data.replace('zodie:', "'zodie':")
    data = data.replace('codsot:', "'codsot':")
    data = data.replace('codtata:', "'codtata':")
    data = data.replace(', tata:', ", 'tata':")
    data = data.replace('codmama:', "'codmama':")
    data = data.replace(', mama:', ", 'mama':")
    data = data.replace('codcopil1:', "'codcopil1':")
    data = data.replace('copil1:', "'copil1':")
    data = data.replace('codcopil2:', "'codcopil2':")
    data = data.replace('copil2:', "'copil2':")
    data = data.replace('codcopil3:', "'codcopil3':")
    data = data.replace('copil3:', "'copil3':")
    data = data.replace('codcopil4:', "'codcopil4':")
    data = data.replace('copil4:', "'copil4':")
    data = data.replace('codcopil5:', "'codcopil5':")
    data = data.replace('copil5:', "'copil5':")
    data = data.replace('codcopil6:', "'codcopil6':")
    data = data.replace('copil6:', "'copil6':")
    data = data.replace('codcopil7:', "'codcopil7':")
    data = data.replace('copil7:', "'copil7':")
    data = data.replace('codcopil8:', "'codcopil8':")
    data = data.replace('copil8:', "'copil8':")
    data = data.replace('codcopil9:', "'codcopil9':")
    data = data.replace('copil9:', "'copil9':")
    data = data.replace('tatanum:', "'tatanum':")
    data = data.replace('mamanum:', "'mamanum':")
    data = data.replace('sotnum:', "'sotnum':")
    data = data.replace('sot:', "'sot':")
    data = data.replace('copilnum1:', "'copilnum1':")
    data = data.replace('copilnum2:', "'copilnum2':")
    data = data.replace('copilnum3:', "'copilnum3':")
    data = data.replace('copilnum4:', "'copilnum4':")
    data = data.replace('copilnum5:', "'copilnum5':")
    data = data.replace('copilnum6:', "'copilnum6':")
    data = data.replace('copilnum7:', "'copilnum7':")
    data = data.replace('copilnum8:', "'copilnum8':")
    data = data.replace('copilnum9:', "'copilnum9':")
    data = data.replace('obs:', "'obs':")
    data = data.replace('numepoza:', "'numepoza':")
    data = data.replace('poza:', "'poza':")

    data = data.replace("'", '"')
    data = data.replace("""},

}""", """}

}""")

    #print (data)

    return json.loads(data)


@app.route("/static/<path:path>")
def static_dir(path):
    return send_from_directory("static", path)


@app.route("/")
def hello_world():
    return """
<html>
<head>
    <script src="static/jquery.js"></script>
</head>
<body>
    <form action="/upload-file" enctype="multipart/form-data" method="POST">
        <input type="file" id="file" name="file"></input>
        <input type="submit" value="Upload">
    </form>
</body>
</html>
"""

@app.route("/upload-file", methods=['GET', 'POST'])
def upload_file():
    if request.method == 'GET':
        return redirect(url_for('hello_world'))
    file_data = request.files['file']
    if file_data == '':
        return redirect(url_for('hello_world'))
    else:
        filename = secure_filename(file_data.filename)
        file_data.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))

    source = open(os.path.join(app.config['UPLOAD_FOLDER'], filename), "r")
    file_content = source.read()
    data = transform_file_input(file_content)

    render = """
<html>
<head>
    <script src="static/jquery.js"></script>
</head>
<body>
    <table>
    {0}
    </table>
</body>
</html>
"""
    output = ""
    for person in data.keys():
        output += "<div>" + data[person]['numepr'] + "<div>"

    return render.format(output)
