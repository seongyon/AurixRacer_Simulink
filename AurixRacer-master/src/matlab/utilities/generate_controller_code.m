function generate_controller_code()
%generate_controller_code
%

%   Copyright 2012 The MathWorks, Inc.

% Use the Simulink Coder API to generate code for controllerModel:

controllerModel = 'IR_Controller';

if(~bdIsLoaded(controllerModel))
    open_system(controllerModel);
end

slbuild(controllerModel);
% coder.report.generate(controllerModel);

!cp ./codegen/IR_Controller_ert_rtw/IR_Controller.c             ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/Algorithm/ert
!cp ./codegen/IR_Controller_ert_rtw/IR_Controller.h             ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/Algorithm/ert
!cp ./codegen/IR_Controller_ert_rtw/IR_Controller_data.c        ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/Algorithm/ert
!cp ./codegen/IR_Controller_ert_rtw/IR_Controller_private.h     ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/Algorithm/ert
!cp ./codegen/IR_Controller_ert_rtw/IR_Controller_types.h       ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/Algorithm/ert
!cp ./codegen/IR_Controller_ert_rtw/rtwtypes.h                  ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/Algorithm/ert
end

