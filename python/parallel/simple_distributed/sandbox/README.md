virtualenv sandbox
echo '''
.Python/
bin/
include/
lib/
.Python
__pycache__
''' >> .gitignore

echo '''
fastapi==0.63.0
uvicorn==0.13.4
''' >> requirements.txt


uvicorn main:app --reload
