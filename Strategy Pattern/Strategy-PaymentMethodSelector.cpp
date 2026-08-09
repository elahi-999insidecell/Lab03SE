#include <iostream>
using namespace std;

// Strategy interface
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

// Concrete Strategies
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paid " << amount << " using Credit Card\n";
    }
};
class PaypalPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paid " << amount << " using PayPal\n";
    }
};
class CODPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Will pay " << amount << " on delivery (COD)\n";
    }
};

// Context
class ShoppingCart {
private:
    PaymentStrategy* strategy;
public:
    void setPaymentStrategy(PaymentStrategy* s) { strategy = s; }
    void checkout(int amount) { strategy->pay(amount); }
};

int main() {
    ShoppingCart cart;

    CreditCardPayment card;
    cart.setPaymentStrategy(&card);
    cart.checkout(500);

    PaypalPayment paypal;
    cart.setPaymentStrategy(&paypal);
    cart.checkout(300);

    return 0;
}