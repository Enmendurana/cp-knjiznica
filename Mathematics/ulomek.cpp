struct ulomek {
    ll num, den;

    ulomek(): num(0), den(1) {}

    ulomek(ll num, ll den) : num(num), den(den) {
        normalize();
    }

    void normalize() {
        if(num == 0) den = 1;
        if(den < 0) {
            den *= -1;
            num *= -1;
        }
        ll d = gcd(num,den);
        num /= d;
        den /= d;
    }

    ulomek operator-() const {
        return ulomek(-num,den);
    }

    ulomek& operator+=(const ulomek &drugi) {
        num = num * drugi.den + drugi.num * den;
        den = den * drugi.den;
        normalize();
        return *this;
    }
    ulomek& operator-=(const ulomek &drugi) {
        num = num * drugi.den - drugi.num * den;
        den = den * drugi.den;
        normalize();
        return *this;
    }
    ulomek& operator*=(const ulomek &drugi) {
        num = (num * drugi.num);
        den = (den * drugi.den);
        normalize();
        return *this;
    }
    ulomek& operator/=(const ulomek &drugi) {
        num = (num * drugi.den);
        den = (den * drugi.num);
        normalize();
        return *this;
    }

};

ulomek operator+(ulomek prvi, const ulomek &drugi) {
    prvi += drugi;
    return prvi;
}
ulomek operator-(ulomek prvi, const ulomek &drugi) {
    prvi -= drugi;
    return prvi;
}
ulomek operator*(ulomek prvi, const ulomek &drugi) {
    prvi *= drugi;
    return prvi;
}
ulomek operator/(ulomek prvi, const ulomek &drugi) {
    prvi /= drugi;
    return prvi;
}

bool operator==(const ulomek &prvi, const ulomek &drugi) {
    return (prvi.num == drugi.num) && (prvi.den == drugi.den);
}

bool operator<(const ulomek &prvi, const ulomek &drugi) {
    return (prvi.num * drugi.den) < (prvi.den * drugi.num);
}

bool operator<=(const ulomek &prvi, const ulomek &drugi) {
    return (prvi < drugi) || (prvi == drugi);
}

bool operator>(const ulomek &prvi, const ulomek &drugi) {
    return drugi < prvi;
}

bool operator>=(const ulomek &prvi, const ulomek &drugi) {
    return drugi <= prvi;
}

ostream& operator<<(ostream &out, const ulomek &prvi) {
    if(prvi.den == 1) {
        out << prvi.num;
    } else {
        out << prvi.num << "/" << prvi.den;
    }
    return out;
}

istream& operator>>(istream &in, ulomek &prvi) {
    in >> prvi.num; prvi.den = 1;
    return in;
}
