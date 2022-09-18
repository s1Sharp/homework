## ------------------------------------------------
## Activate Python venv
## ------------------------------------------------

$pycodepath = "."
$activateEnvPs1 = "$pycodepath\env\Scripts\Activate.ps1"
Set-ExecutionPolicy Unrestricted -Scope Process
. $activateEnvPs1

## ------------------------------------------------
## freeze packages
## ------------------------------------------------

python -m pip freeze > "$pycodepath\requirements.txt"
