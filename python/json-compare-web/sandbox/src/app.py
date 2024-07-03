from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"), name="static")

templates = Jinja2Templates(directory="templates")

envs = ['env1', 'env2']
hosts = {'env1': ['aaa.com', 'bbb.com'], 'env2': ['ccc.com', 'ddd.com']}

@app.post("/compare")
async def compare(request: Request):
    print(request)
    return {"message": "Hello World"}

@app.get("/", response_class=HTMLResponse)
async def index(request: Request):
    return templates.TemplateResponse(request=request, name="index.html", context={'envs': envs, 'hosts': hosts})
