## ------------------------------------------------
## Activate Python venv
## ------------------------------------------------

pycodepath="."
activateEnv="${pycodepath}/env/bin/activate"
source ${activateEnv}

## ------------------------------------------------
## freeze packages
## ------------------------------------------------

python3 -m pip freeze > ${pycodepath}/requirements.txt
