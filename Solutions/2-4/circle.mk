##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=circle
ConfigurationName      :=Debug
WorkspacePath          :=C:/subWork/CheslakovKontext/Solutions
ProjectPath            :=C:/subWork/CheslakovKontext/Solutions/2-4
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Arseny
Date                   :=20/10/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="circle.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/RFiler.cpp$(ObjectSuffix) $(IntermediateDirectory)/Circle.cpp$(ObjectSuffix) $(IntermediateDirectory)/R_IO.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/subWork/CheslakovKontext/Solutions/2-4/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/RFiler.cpp$(ObjectSuffix): RFiler.cpp $(IntermediateDirectory)/RFiler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/subWork/CheslakovKontext/Solutions/2-4/RFiler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RFiler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RFiler.cpp$(DependSuffix): RFiler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/RFiler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/RFiler.cpp$(DependSuffix) -MM RFiler.cpp

$(IntermediateDirectory)/RFiler.cpp$(PreprocessSuffix): RFiler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/RFiler.cpp$(PreprocessSuffix) RFiler.cpp

$(IntermediateDirectory)/Circle.cpp$(ObjectSuffix): Circle.cpp $(IntermediateDirectory)/Circle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/subWork/CheslakovKontext/Solutions/2-4/Circle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Circle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Circle.cpp$(DependSuffix): Circle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Circle.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Circle.cpp$(DependSuffix) -MM Circle.cpp

$(IntermediateDirectory)/Circle.cpp$(PreprocessSuffix): Circle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Circle.cpp$(PreprocessSuffix) Circle.cpp

$(IntermediateDirectory)/R_IO.cpp$(ObjectSuffix): R_IO.cpp $(IntermediateDirectory)/R_IO.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/subWork/CheslakovKontext/Solutions/2-4/R_IO.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/R_IO.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/R_IO.cpp$(DependSuffix): R_IO.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/R_IO.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/R_IO.cpp$(DependSuffix) -MM R_IO.cpp

$(IntermediateDirectory)/R_IO.cpp$(PreprocessSuffix): R_IO.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/R_IO.cpp$(PreprocessSuffix) R_IO.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


