@echo off

:: Only for the home example
echo Run command 'java TestHome' to see results
del Home.class TestHome.class HomeSecurityAspect.class SaveEnergyAspect.class HomeSystemCoordinationAspect.class
ajc Home.java TestHome.java HomeSecurityAspect.aj SaveEnergyAspect.aj HomeSystemCoordinationAspect.aj