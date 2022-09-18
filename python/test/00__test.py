import pytest

from src.main import main
"""Test pytest"""

@pytest.mark.skip("Default skip")
def test_pytest_skip():
    pass

@pytest.mark.xfail()
def test_pytest_xfail():
    assert False == True

def test_pytest_run():
    assert main(None) == None
    return

def test_import():
    from numpy import maximum, minimum
    assert type(maximum) == type(minimum)

# def test_fail():
#     assert False