// _LOGIC_VARIABLES_
//
// vendingState - 0 = Sleep, 1 = Idle, 2 = Turn, 3 = Validate, 4 = Collect, 5 = Finished, 6 = Error
//
// permission bool
// completed  bool
// closed bool
//
// item int
//
// doorOpen bool
// buttonPushed bool
// transactionActive  bool
//
// _FUNCTIONS_
//
// void carrouselLock()
// void carrouselUnlock()
//
// void motorOn()
// void motorOff()
//
// void lightOn()
// void lightOff()
//
// void sireneOn()
// void sireneOff()
//
// void itemUnlock(uint8_t item)
// void itemLock()
//
// void errorOn()
// void errorOff()


void vendingSleep() {
  carrouselLock();
  motorOff();
  lightOff();
  sireneOff();
  itemLock();

  if (buttonPushedState) {
    vendingState = 1; // Idle
    Serial.println("Idle");
    return;
  }
}


void vendingIdle() {
  //implement sleep timer

  carrouselLock();
  motorOff();
  lightOn();
  sireneOff();
  itemLock();

  if (buttonPushedState) {
    vendingState = 2; // Turn
    Serial.println("Turn");
    return;
  }
}


void vendingTurn() {
  if (!carrouselUnlockedState) {
    carrouselUnlock();
    return;
  }

  if (buttonPushedState) {
    if (!motorOnState) {
      motorOn();
      return;
    }
    return;
  }
  else {
    motorOff();
    carrouselLock();
    if (timerButtonPress.read() > UserInputDELAY) {
      vendingState = 3; // Validate
      Serial.println("Validate");
      return;
    }
  }
}


void vendingValidate() {
  // Server Timeout
  if (timerServerTimeout.read() > ServerTimeout) {
    timerServerTimeout.stop();
    transactionActive = false;
    vendingState = 6; // Error
    Serial.println("Error");
    return;
  }

  if (!transactionActive) {
    permissionRequest();
    requestActive = true;
    return;
  }
  else if(transactionActive) {
    requestActive = false;
    vendingState = 4; // Collect
    Serial.println("Collect");
    return;
  }

  if (buttonPushedState) {
    requestActive = false;
    vendingState = 1; // Idle
    Serial.println("Idle");
    return;
  }

}


void vendingCollect(){
  // Purchase Timeout
  if (timerPurchaseTimeout.read() > PurchaseTimeoutDELAY) {
    timerPurchaseTimeout.stop();
    transactionActive = false;
    vendingState = 1; // Idle
    Serial.println("Idle");
    return;
  }

  if (!itemUnlockedState) {
    itemUnlock(item);
    return;
  }

  if (doorOpenState) {
    delay(openDoorDELAY);
    transactionActive = false;
    itemLock();
    completeRequest();
    vendingState = 5; // Finished
    Serial.println("Finished");
    return;
  }
}


void vendingFinished() {
  if (timerDoorOpen.read() > DoorOpenSireneDELAY) {
    sireneOn();
    timerDoorOpen.stop();
  }

  if (!doorOpenState) {
    closeRequest();
    vendingState = 1; // Idle
    Serial.println("Idle");
    return;
  }
}


void vendingError() {
  carrouselLock();
  motorOff();
  lightOff();
  sireneOff();
  itemLock();
  errorOn();

  vendingState = 0; // Sleep
  Serial.println("Sleep");
}
