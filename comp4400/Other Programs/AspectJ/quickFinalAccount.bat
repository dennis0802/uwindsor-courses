@echo off

:: Only for the account example
echo Run command java FinalAccountTest to see results
del Account.class FinalAccountTest.class InsufficientBalanceException.class SavingsAccount.class FinalAccount.class
ajc Account.java SavingsAccount.java InsufficientBalanceException.java FinalAccountTest.java FinalAccount.aj