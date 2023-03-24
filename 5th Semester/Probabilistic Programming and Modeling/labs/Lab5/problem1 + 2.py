import pgmpy
from pgmpy.models import BayesianNetwork
from pgmpy.inference import VariableElimination
from pgmpy.factors.discrete import TabularCPD

# (1) Modelati jocul de carti intr-un model probabilist folosind pgmpy. 

game_model = BayesianNetwork(
    [
        ("Player1", "Player2"),
        ("CarteP2", "DecizieP2"),
        ("CarteP1", "DecizieP1"),
    ]
)

cpd_carte_p1 = TabularCPD(
    variable="CarteP1",
    variable_card=5,
    values=[[0.95, 0.1], [0.05, 0.9], [0.05, 0.1], [0.95, 0.9], [0.05, 0.1]],
)
cpd_carte_p2 = TabularCPD(
    variable="CarteP2",
    variable_card=5,
    values=[[0.95, 0.1], [0.05, 0.9], [0.05, 0.1], [0.95, 0.9], [0.05, 0.1]],
    evidence_card=[1],
)
cpd_decizie_p1 = TabularCPD(
    variable="DecizieP1",
    variable_card=2,
    values=[[0.1, 0.7], [0.9, 0.3]],
    evidence=["CarteP1"],
    evidence_card=[2],
)

cpd_decizie_p2 = TabularCPD(
    variable="DecizieP2",
    variable_card=2,
    values=[[0.1, 0.7], [0.9, 0.3]],
    evidence=["CarteP2","DecizieP1"],
    evidence_card=[2],
)

game_model.add_cpds(
    cpd_carte_p1, cpd_carte_p2, cpd_decizie_p1, cpd_decizie_p2
)

game_model.check_model()

game_model.nodes()

game_model.edges()

game_model.local_independencies("Player1")

game_model.get_independencies()


model_inferential = VariableElimination(game_model)

#EX 2 
# a - esti jucatorul 1 si ai primit un rege de frunza, ar trebui sa pariezi sau nu?

query1 = model_inferential.query(variables=['P1'], evidence={'Card_first_player': 1})
print('first query 1:' ,query1)

#b - esti jucatorul 2 si ai primit un rege de inima iar jucatorul 1 a decis sa parieze , cum ar trb sa decizi?
query2 = model_inferential.query(variables=['P2'], evidence={'P1': 0, 'Card_second_player': 2})
print('first query 2:',query2)

# c - schimbati parametrii strategiilor de pariere - schimb P1 si P2

P1_modified = TabularCPD(variable = 'P1', variable_card = 2,values = [[1, 0.2, 0.6, 0.3, 0],[0, 0.8, 0.4, 0.7, 1]], evidence = ['Card_first_player'],evidence_card=[5])

P2_modified = TabularCPD(variable = 'P2', variable_card=3, values=[[1, 0.8, 0.4, 0.3, 0, 1, 0.8, 0.4, 0.2, 0],[0, 0.2, 0.6, 0.7, 1, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 0, 0.2, 0.6, 0.8, 1]], evidence=['P1', 'Card_second_player'], evidence_card=[2, 5])

print(P1_modified, P2_modified)
