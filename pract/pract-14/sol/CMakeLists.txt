cmake_minimum_required(VERSION 4.2)
project(student_system)

set(CMAKE_CXX_STANDARD 23)

add_executable(student_system main.cpp
        Rocket.cpp
        Rocket.h
        Test.cpp
        Test.h
        Resources.h
        LaunchCondition.cpp
        LaunchCondition.h
        TestCyclesCondition.cpp
        TestCyclesCondition.h
        AverageReliabilityCondition.cpp
        AverageReliabilityCondition.h
        RequiredTestsTakenCondition.cpp
        RequiredTestsTakenCondition.h
        LaunchClearanceService.cpp
        LaunchClearanceService.h
        RocketSystem.cpp
        RocketSystem.h)
