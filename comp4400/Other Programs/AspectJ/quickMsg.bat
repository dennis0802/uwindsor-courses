@echo off

:: Only for the message example
echo Run command 'java MessageTest' to see results
del MessageCommunicator.class MessageTest.class HindiSalutationAspect.class MannersAspect.class
ajc MessageCommunicator.java MessageTest.java HindiSalutationAspect.aj MannersAspect.aj