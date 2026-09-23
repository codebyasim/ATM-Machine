#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, DepositIncreasesBalance) {

    Account account(10001, "Test User", 1000, 1234);

    account.deposit(500);

    EXPECT_DOUBLE_EQ(account.getBalance(), 1500);
}

TEST(AccountTest, WithdrawDecreasesBalance) {

    Account account(10001, "Test User", 1000, 1234);

    account.withdraw(300);

    EXPECT_DOUBLE_EQ(account.getBalance(), 700);
}

TEST(AccountTest, WithdrawMoreThanBalanceThrowsException) {

    Account account(10001, "Test User", 1000, 1234);

    EXPECT_THROW(
        account.withdraw(1500),
        std::runtime_error
    );
}

TEST(AccountTest, CorrectPinIsAccepted) {

    Account account(10001, "Test User", 1000, 1234);

    EXPECT_TRUE(account.verifyPin(1234));
}

TEST(AccountTest, IncorrectPinIsRejected) {

    Account account(10001, "Test User", 1000, 1234);

    EXPECT_FALSE(account.verifyPin(9999));
}

TEST(AccountTest, InvalidDepositThrowsException) {

    Account account(10001, "Test User", 1000, 1234);

    EXPECT_THROW(
        account.deposit(-100),
        std::runtime_error
    );
}

TEST(AccountTest, TransferMovesMoneyBetweenAccounts) {

    Account sender(10001, "Sender", 1000, 1234);
    Account recipient(10002, "Recipient", 500, 5678);

    sender.transfer(recipient, 300);

    EXPECT_DOUBLE_EQ(sender.getBalance(), 700);
    EXPECT_DOUBLE_EQ(recipient.getBalance(), 800);
}
