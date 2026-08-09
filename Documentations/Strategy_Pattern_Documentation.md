# Lab 03 -- Strategy Pattern

## 1. Pattern Name

**Strategy Pattern**

## 2. Category

**Behavioral Design Pattern**

## 3. Intent

The Strategy Pattern defines a family of interchangeable algorithms,
encapsulates each one in its own class, and allows the algorithm to be
selected and swapped at runtime without changing the code that uses it.
It lets the client choose which behavior to use, independent of how that
behavior is implemented.

## 4. Problem Statement

Software systems often need to support several ways of performing the
same task---for example, several payment methods, sorting algorithms, or
route options. Implementing every option as a conditional branch inside
one method forces that method to grow every time a new option is added
and mixes unrelated algorithms together in a single block of code,
making the class harder to test and maintain.

## 5. Motivation

Consider an online shopping cart that must support **Credit Card**,
**PayPal**, and **Cash on Delivery** payments. A naive implementation
checks the payment type directly inside the checkout method:

``` cpp
if (strategy == "credit_card") { payWithCreditCard(); }
else if (strategy == "paypal") { payWithPaypal(); }
else if (strategy == "cod") { payWithCOD(); }
```

Adding a new payment method, such as cryptocurrency, means editing this
method again and risking breaking existing payment logic---a direct
violation of the Open/Closed Principle. The Strategy Pattern solves this
by extracting each payment method into its own class implementing a
common interface, so the `ShoppingCart` class never needs to change when
a new payment method is introduced.

## 6. Pattern Structure (UML Class Diagram)

> **UML diagram:** Add the Strategy Pattern UML image pushed by the team
> to the repository and update the filename below.
>
> `![Strategy Pattern UML](path/to/strategy-pattern-uml.png)`

## 7. Class Responsibilities

-   **PaymentStrategy (Interface)** -- Declares the `pay(amount)`
    operation that every concrete payment method must implement.
-   **CreditCardPayment** -- Implements payment via credit card.
-   **PaypalPayment** -- Implements payment via PayPal.
-   **CODPayment** -- Implements payment via Cash on Delivery.
-   **ShoppingCart (Context)** -- Holds a reference to a
    `PaymentStrategy` and delegates the actual payment work to it during
    checkout, without knowing which concrete strategy is in use.

## 8. Code Implementation

``` cpp
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
```

## 9. Execution Flow (Object Interaction)

1.  The client creates a `ShoppingCart` and a concrete strategy object,
    such as `CreditCardPayment`.
2.  The client calls `cart.setPaymentStrategy(&card)` to inject the
    chosen strategy into the Context.
3.  The client calls `cart.checkout(500)`.
4.  `ShoppingCart` delegates the call to `strategy->pay(500)` without
    knowing how the payment is actually processed.
5.  To switch payment methods, the client assigns a different strategy
    object and calls `checkout()` again. No changes are needed inside
    `ShoppingCart`.

## 10. Advantages

-   Removes conditional logic for selecting an algorithm from the
    Context class.
-   New algorithms (payment methods) can be added as new classes without
    modifying existing code.
-   Each algorithm can be developed, tested, and reused independently.
-   Follows the Open/Closed Principle and supports runtime flexibility.

## 11. Limitations

-   Increases the number of classes for a relatively simple decision.
-   The client must be aware of the different strategies in order to
    choose the correct one.
-   For a very small number of fixed algorithms, the pattern can be
    unnecessary overhead.

## 12. Real-life Applications

-   Payment method selection in e-commerce checkout systems (Amazon,
    Daraz).
-   Route/navigation options in map applications---fastest, shortest,
    avoid tolls.
-   Sorting algorithms selected at runtime (e.g., via a custom
    Comparator).
-   Compression algorithm selection in archiving tools (ZIP vs RAR vs
    7z).
-   Fare calculation strategies in ride-sharing apps (normal fare, surge
    pricing, promo).
-   Authentication strategies (login via Google, Facebook, or
    Email/Password).

## 13. Industry Examples

-   Java's `Collections.sort()` accepts a `Comparator` object, a
    textbook example of the Strategy Pattern.
-   Spring Framework applications commonly inject different strategy
    implementations via dependency injection.
-   Amazon's checkout flow lets users choose among multiple payment
    strategies at runtime.
-   Google Maps lets users switch between driving, walking, transit, and
    cycling as interchangeable routing strategies.

## 14. Conclusion

The Strategy Pattern cleanly separates "what algorithm to use" from "how
the algorithm is used," giving the `ShoppingCart` system the flexibility
to support any number of payment methods without growing a single
conditional block. This makes the system easier to extend, test, and
maintain as new payment options are introduced over time.
