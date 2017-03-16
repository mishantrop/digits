class Digits {
private:
    int value;
    int valueMax;
    int digits[4];
    //int s[13] = {0,2,3,4,5,6,7,8,9,10,11,12,13};
    int s[13];
    int timer;
    int timerMax;

    int buttonIncState;
    int lastbuttonIncState;

    int buttonDecState;
    int lastbuttonDecState;

    int buttonResetState;
    int lastbuttonResetState;

    int buttonIncValue;
    int buttonIncPrev;
    int buttonIncPin;

    int buttonDecValue;
    int buttonDecPrev;
    int buttonDecPin;

    int buttonResetValue;
    int buttonResetPrev;
    int buttonResetPin;

    long lastDebounceIncTime;
    long debounceIncDelay;
    long lastDebounceDecTime;
    long debounceDecDelay;
    long lastDebounceResetTime;
    long debounceResetDelay;

public:
    Digits()
    {
        this->lastbuttonIncState = LOW;

        this->buttonIncValue = LOW;
        this->buttonIncPrev = LOW;
        this->buttonIncPin = 19;

        this->buttonDecValue = LOW;
        this->buttonDecPrev = LOW;
        this->buttonDecPin = 20;

        this->buttonResetValue = LOW;
        this->buttonResetPrev = LOW;
        this->buttonResetPin = 18;

        this->lastDebounceIncTime = 0;
        this->debounceIncDelay = 50;

        // Наверное, первая кнопка ввода
        pinMode(this->buttonIncPin, INPUT);
        pinMode(this->buttonDecPin, INPUT);
        pinMode(this->buttonResetPin, INPUT);

        for (int i = 1; i < 13; i++) {
            this->s[i] = i + 1;
            pinMode(s[i], OUTPUT);
        }

        this->value = 0;
        this->valueMax = 0xfff;
        this->timerMax = 128;
        this->timer = this->timerMax;

        for (int i = 0; i < 4; i++) {
            digits[i] = 0;
        }
    }
    void Delay(int time)
    {
        delay(time);
    }

    void DrawNumber(int n)
    {
        digitalWrite(s[1], LOW);
        digitalWrite(s[2], LOW);
        digitalWrite(s[3], LOW);
        digitalWrite(s[4], LOW);
        digitalWrite(s[5], LOW);
        digitalWrite(s[7], LOW);
        digitalWrite(s[10], LOW);
        digitalWrite(s[11], LOW);
        switch (n) {
        case 0:
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 1:
            digitalWrite(s[4], HIGH);
            digitalWrite(s[7], HIGH);
            break;
        case 2:
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 3:
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 4:
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[10], HIGH);
            break;
        case 5:
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 6:
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 7:
            digitalWrite(s[4], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 8:
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 9:
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 10: // A
            digitalWrite(s[1], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 11: // B
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[10], HIGH);
            break;
        case 12: // C
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 13: // D
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[4], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[7], HIGH);
            break;
        case 14: // E
            digitalWrite(s[1], HIGH);
            digitalWrite(s[2], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        case 15: // F
            digitalWrite(s[1], HIGH);
            digitalWrite(s[5], HIGH);
            digitalWrite(s[10], HIGH);
            digitalWrite(s[11], HIGH);
            break;
        default:
            break;
        }
    }

    /**
	 * Переключиться на разряд с номером n
	 */
    void SwitchDigit(int n)
    {
        this->Clear();

        switch (n) {
        case 0:
            digitalWrite(s[6], LOW);
            break;
        case 1:
            digitalWrite(s[8], LOW);
            break;
        case 2:
            digitalWrite(s[9], LOW);
            break;
        case 3:
            digitalWrite(s[12], LOW);
            break;
        }
    }

    void Loop()
    {

        this->buttonIncValue = digitalRead(this->buttonIncPin);
        this->buttonDecValue = digitalRead(this->buttonDecPin);
        this->buttonResetValue = digitalRead(this->buttonResetPin);

        /* Первая кнопка */
        if (this->buttonIncValue != this->lastbuttonIncState) {
            this->lastDebounceIncTime = millis();
        }

        if ((millis() - this->lastDebounceIncTime) > this->debounceIncDelay) {
            if (this->buttonIncValue != this->buttonIncState) {
                this->buttonIncState = this->buttonIncValue;
                if (this->buttonIncState == HIGH) {
                    this->value++;
                }
            }
        }
        this->lastbuttonIncState = this->buttonIncValue;

        /* Вторая кнопка */
        if (this->buttonDecValue != this->lastbuttonDecState) {
            this->lastDebounceDecTime = millis();
        }

        if ((millis() - this->lastDebounceDecTime) > this->debounceDecDelay) {
            if (this->buttonDecValue != this->buttonDecState) {
                this->buttonDecState = this->buttonDecValue;
                if (this->buttonDecState == HIGH) {
                    this->value += 0x25;
                }
            }
        }
        this->lastbuttonDecState = this->buttonDecValue;

        /* Третья кнопка */
        if (this->buttonResetValue != this->lastbuttonResetState) {
            this->lastDebounceResetTime = millis();
        }

        if ((millis() - this->lastDebounceResetTime) > this->debounceResetDelay) {
            if (this->buttonResetValue != this->buttonResetState) {
                this->buttonResetState = this->buttonResetValue;
                if (this->buttonResetState == HIGH) {
                    this->value = 0x100;
                }
            }
        }
        this->lastbuttonResetState = this->buttonResetValue;

        if (this->value > this->valueMax || this->value < 0) {
            this->value = 0;
        }
        this->CalcDigits();

        for (int i = 0; i < 4; i++) {
            this->SwitchDigit(i);
            this->DrawNumber(digits[i]);
            this->Delay(10);
            //delayMicroseconds(1000000);
        }
    }

    void CalcDigits()
    {
        //digits[3][2][1][0]

        // Младший разряд
        digits[1] = this->value % 16;

        // Средний раздел
        digits[2] = this->value / 16 % 16;

        // Старший раздел
        digits[3] = this->value / 256 % 16;

        // Вычисление минимального разряда
        digits[0] = (digits[1] >= digits[2]) ? digits[2] : digits[1];
        digits[0] = (digits[0] >= digits[3]) ? digits[3] : digits[0];
    }

    void Clear()
    {
        digitalWrite(s[6], HIGH);
        digitalWrite(s[8], HIGH);
        digitalWrite(s[9], HIGH);
        digitalWrite(s[12], HIGH);

        digitalWrite(s[1], LOW);
        digitalWrite(s[2], LOW);
        digitalWrite(s[4], LOW);
        digitalWrite(s[5], LOW);
        digitalWrite(s[7], LOW);
        digitalWrite(s[10], LOW);
        digitalWrite(s[11], LOW);
    }
};

Digits a;

void setup()
{
}

void loop()
{
    a.Loop();
}
