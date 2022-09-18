How to set up environment
Linux:

python3 -m venv env
source env/bin/activate
python3 -m pip install -r requirements.txt
Windows:

python -m venv env
.\env\Scripts\activate.bat
python -m pip install -r requirements.txt
For deactivate the Python venv:

deactivate
Update requirements
pip freeze > requirements.txt