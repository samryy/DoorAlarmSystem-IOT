boolean outDoorClosed = false;
boolean communityDoorClosed = false;
boolean coming = false;
boolean going = false;
boolean guardMode = false;
boolean outDoorClosedPre = false;
boolean communityDoorClosedPre = false;
boolean welcomeReady = false;
boolean goodByeReady = false;
boolean alarmOn = false;
boolean firstAlarmdone = false;
int comCounter = 0;
float x = -8888;

void setup() {
        Serial.begin(115200);
        pinMode(LED_BUILTIN, OUTPUT);
        pinMode(2, INPUT_PULLUP);
        pinMode(3, INPUT_PULLUP);
}

String serialHttpGet(String url) {
        Serial.print("GET ");
        Serial.println(url);
        return Serial.readStringUntil('\n');
}

float serialHttpGetFloat(String url) {
        String s = serialHttpGet(url);
        return s.toFloat();
}

void checkIfCommunication() {
        if(comCounter == 5) {
                x = serialHttpGetFloat("http://one.api.botbook.com/last/wx8ETBcLFey");
                if(x == 66) {
                        guardMode = true;
                } if(x == 55) {
                        guardMode = false;
                } if(x == 44) {
                        alarmOn = false;
                        firstAlarmdone = false;
                } if(x == 33) {
                        if(outDoorClosed == true && communityDoorClosed == true) {
                                Serial.println("GET http://one.api.botbook.com/add/4kzxV3BUgl7/?x=10");
                        }
                        if(outDoorClosed == true && communityDoorClosed == false) {
                                Serial.println("GET http://one.api.botbook.com/add/4kzxV3BUgl7/?x=11");
                        }
                        if(outDoorClosed == false && communityDoorClosed == true) {
                                Serial.println("GET http://one.api.botbook.com/add/4kzxV3BUgl7/?x=12");
                        }
                        if(outDoorClosed == false && communityDoorClosed == false) {
                                Serial.println("GET http://one.api.botbook.com/add/4kzxV3BUgl7/?x=13");
                        }
                }


                comCounter = 0;
        }
        comCounter = comCounter + 1;
}

void loop() {
        checkIfCommunication();
        getDoorStatus();
        checkChange();

        if(coming == true) {
                checkWelcome();
        }
        if(going == true) {
                checkGoodBye();
        }

        if(welcomeReady == true) {
                readyForWelcome();

        }
        if(goodByeReady == true) {
                readyForGoodBye();
        }

        if(guardMode == true) {
                homeDefenseCheck();
        }

        if(alarmOn == true) {
                digitalWrite(LED_BUILTIN, HIGH);
        }else{
                digitalWrite(LED_BUILTIN, LOW);
        }

        checkReset();
        delay(50);
}

void getDoorStatus(){
        if (digitalRead(2) == HIGH ) {
                outDoorClosed = true;
        }else{
                outDoorClosed = false;
        }
        if (digitalRead(3) == HIGH ) {
                communityDoorClosed = true;
        }else{
                communityDoorClosed = false;
        }
}

void checkChange(){
        if(outDoorClosed != outDoorClosedPre) {
                if(going == false) {
                        checkIfComing();
                }
        }
        if(communityDoorClosed != communityDoorClosedPre) {
                if(coming == false) {
                        checkIfGoing();
                }
        }
        communityDoorClosedPre = communityDoorClosed;
        outDoorClosedPre = outDoorClosed;
}

void checkIfComing(){
        if(communityDoorClosed ==  true && outDoorClosed == false) {
                coming = true;
        }
}
void checkIfGoing(){
        if(outDoorClosed == true && communityDoorClosed == false) {
                going = true;
        }
}

void checkReset(){
        if(outDoorClosed == true && communityDoorClosed == true) {
                coming = false;
                going = false;
        }
}

void checkWelcome(){
        if(communityDoorClosed == false) {
                welcomeReady = true;
                coming = false;
                going = false;
        }
}
void checkGoodBye(){
        if(outDoorClosed == false) {
                goodByeReady = true;
                coming = false;
                going = false;
        }
}

void readyForWelcome(){
        if(communityDoorClosed == true) {
                welcomeReady = false;
        }
}
void readyForGoodBye(){
        if(outDoorClosed == true) {
                goodByeReady = false;
        }
}

void homeDefenseCheck(){
        if(going == false && goodByeReady == false && outDoorClosed == false) {
                alarmOn = true;
                if(firstAlarmdone == false) {
                        Serial.println("GET http://one.api.botbook.com/add/4kzxV3BUgl7/?x=100");
                        firstAlarmdone = true;
                }
        }
}
