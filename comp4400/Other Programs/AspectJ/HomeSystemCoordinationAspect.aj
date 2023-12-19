public aspect HomeSystemCoordinationAspect{
    declare precedence: HomeSecurityAspect, SaveEnergyAspect;
}