BIN = bin
SRC = fuentes
OBJ = obj
INCLUDE = includes
COMPILER = -std=c++0x
OPT = -O2

CXX = g++

all: $(BIN)/mainLS $(BIN)/mainAGGPos $(BIN)/mainAGGOX $(BIN)/mainGreedy $(BIN)/mainAGEPos $(BIN)/mainAGEOX $(BIN)/mainAMFull\
	 $(BIN)/mainAMSub $(BIN)/mainAMElite $(BIN)/mainGeneral

LS: $(BIN)/mainLS
AGGPos: $(BIN)/mainAGGPos
AGGOX: $(BIN)/mainAGGOX
Greedy: $(BIN)/mainGreedy
AGEPos: $(BIN)/mainAGEPos
AGEOX: $(BIN)/mainAGEOX
AMFull: $(BIN)/mainAMFull
AMSub: $(BIN)/mainAMSub
AMElite: $(BIN)/mainAMElite
General: $(BIN)/mainGeneral

###### Obtencion de los ejecutables ######

$(BIN)/mainGreedy: $(OBJ)/mainGreedy.o $(OBJ)/QAP.o $(OBJ)/Greedy.o
	@$(CXX) -o $(BIN)/mainGreedy $(OBJ)/mainGreedy.o $(OBJ)/QAP.o $(OBJ)/Greedy.o $(OPT)
	@echo "Compilando mainGreedy..."

$(BIN)/mainLS: $(OBJ)/mainLS.o $(OBJ)/QAP.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainLS $(OBJ)/mainLS.o $(OBJ)/QAP.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainLS..."

$(BIN)/mainAGGPos: $(OBJ)/mainAGGPos.o $(OBJ)/QAP.o $(OBJ)/AGGPos.o
	@$(CXX) -o $(BIN)/mainAGGPos $(OBJ)/mainAGGPos.o $(OBJ)/QAP.o $(OBJ)/AGGPos.o $(OPT)
	@echo "Compilando mainAGGPos..."

$(BIN)/mainAGGOX: $(OBJ)/mainAGGOX.o $(OBJ)/QAP.o $(OBJ)/AGGOX.o
	@$(CXX) -o $(BIN)/mainAGGOX $(OBJ)/mainAGGOX.o $(OBJ)/QAP.o $(OBJ)/AGGOX.o $(OPT)
	@echo "Compilando mainAGGOX..."

$(BIN)/mainAGEPos: $(OBJ)/mainAGEPos.o $(OBJ)/QAP.o $(OBJ)/AGEPos.o
	@$(CXX) -o $(BIN)/mainAGEPos $(OBJ)/mainAGEPos.o $(OBJ)/QAP.o $(OBJ)/AGEPos.o $(OPT)
	@echo "Compilando mainAGEPos..."

$(BIN)/mainAGEOX: $(OBJ)/mainAGEOX.o $(OBJ)/QAP.o $(OBJ)/AGEOX.o
	@$(CXX) -o $(BIN)/mainAGEOX $(OBJ)/mainAGEOX.o $(OBJ)/QAP.o $(OBJ)/AGEOX.o $(OPT)
	@echo "Compilando mainAGEOX..."

$(BIN)/mainAMFull: $(OBJ)/mainAMFull.o $(OBJ)/QAP.o $(OBJ)/AMFull.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainAMFull $(OBJ)/mainAMFull.o $(OBJ)/QAP.o $(OBJ)/AMFull.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainAMFull..."

$(BIN)/mainAMSub: $(OBJ)/mainAMSub.o $(OBJ)/QAP.o $(OBJ)/AMSub.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainAMSub $(OBJ)/mainAMSub.o $(OBJ)/QAP.o $(OBJ)/AMSub.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainAMSub..."

$(BIN)/mainAMElite: $(OBJ)/mainAMElite.o $(OBJ)/QAP.o $(OBJ)/AMElite.o $(OBJ)/LS.o
	@$(CXX) -o $(BIN)/mainAMElite $(OBJ)/mainAMElite.o $(OBJ)/QAP.o $(OBJ)/AMElite.o $(OBJ)/LS.o $(OPT)
	@echo "Compilando mainAMElite..."

$(BIN)/mainGeneral: $(OBJ)/mainGeneral.o $(OBJ)/QAP.o $(OBJ)/AGGPos.o $(OBJ)/LS.o $(OBJ)/Greedy.o $(OBJ)/AGGOX.o $(OBJ)/AGEPos.o\
													  $(OBJ)/AGEOX.o $(OBJ)/AMFull.o $(OBJ)/AMSub.o $(OBJ)/AMElite.o
	@$(CXX) -o $(BIN)/mainGeneral $(OBJ)/mainGeneral.o $(OBJ)/QAP.o $(OBJ)/AGGPos.o $(OBJ)/LS.o $(OBJ)/Greedy.o $(OBJ)/AGGOX.o\
													   $(OBJ)/AGEPos.o $(OBJ)/AGEOX.o $(OBJ)/AMFull.o $(OBJ)/AMSub.o $(OBJ)/AMElite.o $(OPT)
	@echo "Compilando mainGeneral..."

###### Compilacion de los codigos objeto de los ejecutables ######

$(OBJ)/mainGreedy.o: $(SRC)/mainGreedy.cpp 
	@$(CXX) -c -o $(OBJ)/mainGreedy.o $(SRC)/mainGreedy.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainGreedy..."

$(OBJ)/mainLS.o: $(SRC)/mainLS.cpp
	@$(CXX) -c -o $(OBJ)/mainLS.o $(SRC)/mainLS.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainLS..."

$(OBJ)/mainAGGPos.o: $(SRC)/mainAGGPos.cpp
	@$(CXX) -c -o $(OBJ)/mainAGGPos.o $(SRC)/mainAGGPos.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAGGPos..."

$(OBJ)/mainAGGOX.o: $(SRC)/mainAGGOX.cpp
	@$(CXX) -c -o $(OBJ)/mainAGGOX.o $(SRC)/mainAGGOX.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAGGOX..."

$(OBJ)/mainAGEPos.o: $(SRC)/mainAGEPos.cpp
	@$(CXX) -c -o $(OBJ)/mainAGEPos.o $(SRC)/mainAGEPos.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAGEPos..."

$(OBJ)/mainAGEOX.o: $(SRC)/mainAGEOX.cpp
	@$(CXX) -c -o $(OBJ)/mainAGEOX.o $(SRC)/mainAGEOX.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAGEOX..."

$(OBJ)/mainAMFull.o: $(SRC)/mainAMFull.cpp
	@$(CXX) -c -o $(OBJ)/mainAMFull.o $(SRC)/mainAMFull.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAMFull..."

$(OBJ)/mainAMSub.o: $(SRC)/mainAMSub.cpp
	@$(CXX) -c -o $(OBJ)/mainAMSub.o $(SRC)/mainAMSub.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAMSub..."

$(OBJ)/mainAMElite.o: $(SRC)/mainAMElite.cpp
	@$(CXX) -c -o $(OBJ)/mainAMElite.o $(SRC)/mainAMElite.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto mainAMElite..."

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

$(OBJ)/AGGPos.o: $(SRC)/AGGPos.cpp
	@$(CXX) -c -o $(OBJ)/AGGPos.o $(SRC)/AGGPos.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AGGPos..."

$(OBJ)/AGGOX.o: $(SRC)/AGGOX.cpp
	@$(CXX) -c -o $(OBJ)/AGGOX.o $(SRC)/AGGOX.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AGGOX..."

$(OBJ)/AGEPos.o: $(SRC)/AGEPos.cpp
	@$(CXX) -c -o $(OBJ)/AGEPos.o $(SRC)/AGEPos.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AGEPos..."

$(OBJ)/AGEOX.o: $(SRC)/AGEOX.cpp
	@$(CXX) -c -o $(OBJ)/AGEOX.o $(SRC)/AGEOX.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AGEOX..."

$(OBJ)/AMFull.o: $(SRC)/AMFull.cpp
	@$(CXX) -c -o $(OBJ)/AMFull.o $(SRC)/AMFull.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AMFull..."

$(OBJ)/AMSub.o: $(SRC)/AMSub.cpp
	@$(CXX) -c -o $(OBJ)/AMSub.o $(SRC)/AMSub.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AMSub..."

$(OBJ)/AMElite.o: $(SRC)/AMElite.cpp
	@$(CXX) -c -o $(OBJ)/AMElite.o $(SRC)/AMElite.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto AMElite..."

$(OBJ)/QAP.o: $(SRC)/QAP.cpp 
	@$(CXX) -c -o $(OBJ)/QAP.o $(SRC)/QAP.cpp -I$(INCLUDE) $(COMPILER) $(OPT)
	@echo "Compilando código objeto QAP..."


clean:
	@echo "Eliminando ejecutables y ficheros objeto..."
	@rm -f $(OBJ)/* $(BIN)/*
