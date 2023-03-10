
void
SimCarUpdate(tCar *car, tSituation * /* s */)
{
    SimCarUpdateForces(car);
    CHECK(car);
    SimCarUpdateSpeed(car);
    CHECK(car);
    SimCarUpdateCornerPos(car);
    CHECK(car);
    SimCarUpdatePos(car);
    CHECK(car);
    SimCarCollideZ(car);
    CHECK(car);
    SimCarCollideXYScene(car);
    CHECK(car);
}
```