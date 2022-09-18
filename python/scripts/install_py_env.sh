## ------------------------------------------------
## set env variables
## ------------------------------------------------
pycodepath="."
activateEnv="${pycodepath}/env/bin/activate"

## ------------------------------------------------
## Install Python venv
## ------------------------------------------------
sudo apt-get install python3-venv python-pip -y
python3 -m venv env

## ------------------------------------------------
## Activate Python venv
## ------------------------------------------------

source ${activateEnv}
python3 -m pip3 install -r ${pycodepath}/requirements.txt

echo $(pip list)

## ------------------------------------------------
## Run pytest
## ------------------------------------------------

python3 -m pytest
