#include "Controller/MyController.h"

void MyController::setControllerListener(ControllerListener* controllerListener)
{
	this->m_controllerListener = controllerListener;

}

void MyController::setiXSpeed(int iSpeed)
{
	this->m_iXSpeed = iSpeed;
}

void MyController::setiYSpeed(int iSpeed)
{
	this->m_iYSpeed = iSpeed;
}