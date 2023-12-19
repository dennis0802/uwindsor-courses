@echo off

:: Only for the account example
echo Run command java AccountTest to see results
del Account.class AccountTest.class InsufficientBalanceException.class JoinPointTraceAspect.class SavingsAccount.class
ajc Account.java SavingsAccount.java InsufficientBalanceException.java AccountTest.java JoinPointTraceAspect.aj