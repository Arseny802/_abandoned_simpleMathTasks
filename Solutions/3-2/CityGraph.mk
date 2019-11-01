##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CityGraph
ConfigurationName      :=Debug
WorkspacePath          :=/home/arseny/Documents/subWork/CheslakovKontext/Solutions
ProjectPath            :=/home/arseny/Documents/subWork/CheslakovKontext/Solutions/3-2
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Arseny
Date                   :=01/11/19
CodeLitePath           :=/home/arseny/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
ObjectsFileList        :="CityGraph.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/CityGraph.cc$(ObjectSuffix) $(IntermediateDirectory)/main.cc$(ObjectSuffix) $(IntermediateDirectory)/ReaderIo.cc$(ObjectSuffix) $(IntermediateDirectory)/RFiler.cc$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/CityGraph.cc$(ObjectSuffix): CityGraph.cc $(IntermediateDirectory)/CityGraph.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/arseny/Documents/subWork/CheslakovKontext/Solutions/3-2/CityGraph.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CityGraph.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CityGraph.cc$(DependSuffix): CityGraph.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CityGraph.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/CityGraph.cc$(DependSuffix) -MM CityGraph.cc

$(IntermediateDirectory)/CityGraph.cc$(PreprocessSuffix): CityGraph.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CityGraph.cc$(PreprocessSuffix) CityGraph.cc

$(IntermediateDirectory)/main.cc$(ObjectSuffix): main.cc $(IntermediateDirectory)/main.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/arseny/Documents/subWork/CheslakovKontext/Solutions/3-2/main.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cc$(DependSuffix): main.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cc$(DependSuffix) -MM main.cc

$(IntermediateDirectory)/main.cc$(PreprocessSuffix): main.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cc$(PreprocessSuffix) main.cc

$(IntermediateDirectory)/ReaderIo.cc$(ObjectSuffix): ReaderIo.cc $(IntermediateDirectory)/ReaderIo.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/arseny/Documents/subWork/CheslakovKontext/Solutions/3-2/ReaderIo.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ReaderIo.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ReaderIo.cc$(DependSuffix): ReaderIo.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ReaderIo.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/ReaderIo.cc$(DependSuffix) -MM ReaderIo.cc

$(IntermediateDirectory)/ReaderIo.cc$(PreprocessSuffix): ReaderIo.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ReaderIo.cc$(PreprocessSuffix) ReaderIo.cc

$(IntermediateDirectory)/RFiler.cc$(ObjectSuffix): RFiler.cc $(IntermediateDirectory)/RFiler.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/arseny/Documents/subWork/CheslakovKontext/Solutions/3-2/RFiler.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RFiler.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RFiler.cc$(DependSuffix): RFiler.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/RFiler.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/RFiler.cc$(DependSuffix) -MM RFiler.cc

$(IntermediateDirectory)/RFiler.cc$(PreprocessSuffix): RFiler.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/RFiler.cc$(PreprocessSuffix) RFiler.cc


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


