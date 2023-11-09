void vendingSleep() {
  timerSleep.stop();
  carrouselLock();
  motorOff();
  lightOff();
  sireneOff();
  itemLock();

  if (buttonTurnPushedState) {
    timerSleep.stop();
    timerSleep.start();
    vendingState = 1; // Idle
    Serial.println("sleep --> Idle");
    return;
  }
}


void vendingIdle() {
  if (timerSleep.read() > SleepDELAY) {
    timerSleep.stop();
    vendingState = 0; // Sleep
    Serial.println("idle --> Sleep");
    return;
  }

  carrouselLock();
  motorOff();
  lightOn();
  sireneOff();
  itemLock();

  if (buttonTurnPushedState) {
    vendingState = 2; // Turn
    Serial.println("idle --> Turn");
    return;
  }
  if (buttonOpenPushedState) {
    vendingState = 3; // Validate
    Serial.println("idle --> Validate");
    return;
  }
}


void vendingTurn() {
  if (!carrouselUnlockedState) {
    carrouselUnlock();
    return;
  }

  if (buttonTurnPushedState) {
    if (!motorOnState) {
      motorOn();
      return;
    }
    return;
  }
  else {
    carrouselLock();
    delay(MotorTurnDELAY);
    motorOff();
    carrouselLock();
    timerSleep.stop();
    timerSleep.start();

    vendingState = 1; // Idle
    Serial.println("turn --> Idle");
    return;
  }
}


void vendingValidate() {
  // Server Timeout
  /*
  if (timerServerTimeout.read() > ServerTimeout) {
    timerServerTimeout.stop();
    transactionActive = false;
    requestActive = false;
    vendingState = 6; // Error
    Serial.println("validate --> Error");
    return;
  }
  */

  if (!transactionActive) {
    permissionRequest();
    requestActive = true;
  }
  else if(transactionActive) {
    timerServerTimeout.stop();
    requestActive = false;
    vendingState = 4; // Collect
    Serial.println("validate --> Collect");
    return;
  }
}


void vendingCollect(){
  // Purchase Timeout
  /*
  if (timerPurchaseTimeout.read() > PurchaseTimeoutDELAY) {
    timerPurchaseTimeout.stop();
    transactionActive = false;
    timerSleep.stop();
    timerSleep.start();

    vendingState = 1; // Idle
    Serial.println("collect --> idle");
    return;
  }
  */
  if (!itemUnlockedState && !doorOpenState) {
    itemUnlock(item);
    return;
  }

  if (doorOpenState && transactionActive) {
    delay(openDoorDELAY);
    itemLock();
    if( completeRequest() ) {
      timerPurchaseTimeout.stop();
      timerServerTimeout.start();
      transactionActive = false;
      vendingState = 5; // Finished
      Serial.println("collect --> finished");
      return;
    }
  }
}


void vendingFinished() {
  /*
  if (timerDoorOpen.read() > DoorOpenSireneDELAY) {
    sireneOn();
    timerDoorOpen.stop();
  }
*/
  if (!doorOpenState) {
    sireneOff();
    timerDoorOpen.stop();
    if ( closeRequest()) {
      timerServerTimeout.stop();
      timerSleep.stop();
      timerSleep.start();
      vendingState = 1; // Idle
      Serial.println("Finished --> Idle");
      return;
    }
    if (timerServerTimeout.read() > ServerTimeout) {
      timerServerTimeout.stop();
      vendingState = 6; // Error
      Serial.println("Finished --> error");
      return;
    }
  }
}


void vendingError() {
  carrouselLock();
  motorOff();
  lightOff();
  //sireneOff();
  sireneOn();
  itemLock();
  errorOn();

  vendingState = 0; // Sleep
  Serial.println("Error --> Sleep");
}
