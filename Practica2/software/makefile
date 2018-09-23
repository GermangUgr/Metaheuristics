BIN = bin
SRC = fuentes
OBJ = obj
INCLUDE = includes
COMPILER = -std=c++0x
OPT = -O2

CXX = g++

all: $(BIN)/mainGreedy $(BIN)/mainLS $(BIN)/mainSA $(BIN)/mainGRASP $(BIN)/mainILS $(BIN)/mainBMS $(BIN)/mainILSSA $(BIN)/mainGeneral

Greedy: $(BIN)/mainGreedy
LS: $(BIN)/mainLS
SA: $(BIN)/mainSA
GRASP: $(BIN)/mainGRASP
ILS: $(BIN)/mainILS
BMS: $(BIN)/mainBMS
ILSSA: $(BIN)/mainILSSA
General: $(BIN)/mainGeneral

###### Obtencion de los ejecutables ######

$(BIN)/mainGreedy: $(OBJ)/mainGreedy.o $(OBJ)/QAP.o $(OBJ)/Greedy.o
	@$(CXX) -o $(BIN)/mainGreedy $(OBJ)/mainGreedy.o $(OBJ)/QAP.o $(OBJ)/Greedy.o $(OPT)
	@echo "Compilando mainGreedy..."

$(BIN)/mainLS: $(OBJ)/mainLS.o $(OBJ)/QAP.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainLS $(OBJ)/mainLS.o $(OBJ)/QAP.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainLS..."

$(BIN)/mainSA: $(OBJ)/mainSA.o $(OBJ)/QAP.o $(OBJ)/SA.o
	@$(CXX) -o $(BIN)/mainSA $(OBJ)/mainSA.o $(OBJ)/QAP.o $(OBJ)/SA.o $(OPT)
	@echo "Compilando mainSA..."

$(BIN)/mainGRASP: $(OBJ)/mainGRASP.o $(OBJ)/QAP.o $(OBJ)/GRASP.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainGRASP $(OBJ)/mainGRASP.o $(OBJ)/QAP.o $(OBJ)/GRASP.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainGRASP..."

$(BIN)/mainILS: $(OBJ)/mainILS.o $(OBJ)/QAP.o $(OBJ)/ILS.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainILS $(OBJ)/mainILS.o $(OBJ)/QAP.o $(OBJ)/ILS.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainILS..."

$(BIN)/mainBMS: $(OBJ)/mainBMS.o $(OBJ)/QAP.o $(OBJ)/BMS.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainBMS $(OBJ)/mainBMS.o $(OBJ)/QAP.o $(OBJ)/BMS.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainBMS..."

$(BIN)/mainILSSA: $(OBJ)/mainILSSA.o $(OBJ)/QAP.o $(OBJ)/ILSSA.o $(OBJ)/SA.o
	@$(CXX) -o $(BIN)/mainILSSA $(OBJ)/mainILSSA.o $(OBJ)/QAP.o $(OBJ)/ILSSA.o $(OBJ)/SA.o $(OPT)
	@echo "Compilando mainILSSA..."

$(BIN)/mainGeneral: $(OBJ)/mainGeneral.o $(OBJ)/QAP.o $(OBJ)/Greedy.o $(OBJ)/LS.o $(OBJ)/SA.o $(OBJ)/GRASP.o $(OBJ)/ILS.o\
													  $(OBJ)/BMS.o $(OBJ)/ILSSA.o
	@$(CXX) -o $(BIN)/mainGeneral $(OBJ)/mainGeneral.o $(OBJ)/QAP.o $(OBJ)/Greedy.o $(OBJ)/LS.o $(OBJ)/SA.o $(OBJ)/GRASP.o $(OBJ)/ILS.o\
													  $(OBJ)/BMS.o $(OBJ)/ILSSA.o
	@echo "Compilando mainGeneral..."

###### Compilacion de los codigos objeto de los ejecutables ######

$(OBJ)/mainGreedy.o: $(SRC)/mainGreedy.cpp 
	@$(CXX) -c -o $(OBJ)/mainGreedy.o $(SRC)/mainGreedy.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainGreedy..."

$(OBJ)/mainLS.o: $(SRC)/mainLS.cpp
	@$(CXX) -c -o $(OBJ)/mainLS.o $(SRC)/mainLS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainLS..."

$(OBJ)/mainSA.o: $(SRC)/mainSA.cpp 
	@$(CXX) -c -o $(OBJ)/mainSA.o $(SRC)/mainSA.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainSA..."

$(OBJ)/mainGRASP.o: $(SRC)/mainGRASP.cpp 
	@$(CXX) -c -o $(OBJ)/mainGRASP.o $(SRC)/mainGRASP.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainGRASP..."

$(OBJ)/mainILS.o: $(SRC)/mainILS.cpp 
	@$(CXX) -c -o $(OBJ)/mainILS.o $(SRC)/mainILS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainILS..."

$(OBJ)/mainBMS.o: $(SRC)/mainBMS.cpp 
	@$(CXX) -c -o $(OBJ)/mainBMS.o $(SRC)/mainBMS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainBMS..."

$(OBJ)/mainILSSA.o: $(SRC)/mainILSSA.cpp 
	@$(CXX) -c -o $(OBJ)/mainILSSA.o $(SRC)/mainILSSA.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainILSSA..."

$(OBJ)/mainGeneral.o: $(SRC)/mainGeneral.cpp
	@$(CXX) -c -o $(OBJ)/mainGeneral.o $(SRC)/mainGeneral.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainGeneral..."

###### Compilacion de los codigos objeto de los algortimos ######

$(OBJ)/Greedy.o: $(SRC)/Greedy.cpp
	@$(CXX) -c -o $(OBJ)/Greedy.o $(SRC)/Greedy.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto Greedy..."

$(OBJ)/LS.o: $(SRC)/LS.cpp
	@$(CXX) -c -o $(OBJ)/LS.o $(SRC)/LS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto LS..."

$(OBJ)/SA.o: $(SRC)/SA.cpp
	@$(CXX) -c -o $(OBJ)/SA.o $(SRC)/SA.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto SA..."

$(OBJ)/GRASP.o: $(SRC)/GRASP.cpp 
	@$(CXX) -c -o $(OBJ)/GRASP.o $(SRC)/GRASP.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto GRASP..."

$(OBJ)/ILS.o: $(SRC)/ILS.cpp 
	@$(CXX) -c -o $(OBJ)/ILS.o $(SRC)/ILS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto ILS..."

$(OBJ)/BMS.o: $(SRC)/BMS.cpp 
	@$(CXX) -c -o $(OBJ)/BMS.o $(SRC)/BMS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto BMS..."

$(OBJ)/ILSSA.o: $(SRC)/ILSSA.cpp 
	@$(CXX) -c -o $(OBJ)/ILSSA.o $(SRC)/ILSSA.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto ILSSA..."

$(OBJ)/QAP.o: $(SRC)/QAP.cpp 
	@$(CXX) -c -o $(OBJ)/QAP.o $(SRC)/QAP.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto QAP..."


clean:
	@echo "Eliminando ejecutables y ficheros objeto..."
	@rm -f $(OBJ)/* $(BIN)/*
