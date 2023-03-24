<h1>Laboratory 7</h1>

For the compulsory part, I have done the following:
<ul>
    <li>three main classes: the GameManager class, the Player class and the Token class. Each one does a different thing:
        <ul>
            <li>the GameManager class : it handles the whole game, adding players, running them and printing the scores when the game ended. Also it prints the game table.</li>
            <li>the Player class : it has a name and a list of tokens. It also handles the interaction between the game board and its list of tokens. It uses a lock to access the game board (with <em>synchonized</em>).</li>
            <li>the Token class : it describes a token from the game, having all the attributes described in the laboratory description.</li>
        </ul>
    </li>
    <li>added a simple console interface for setting up the game (number of players, number of tokens, the minimum and maximum score for a token, etc)</li>
    <li>in the Main class, there are two static functions: <em>setupGame</em> and <em>startGame</em>, each doing a specific task.</li>
</ul>

For the optional part, I have done the following:
<ul>
    <li>the class Player was made abstract and two other classes were added: ComputerPlayer and HumanPlayer. The ComputerPlayer is a bot, while the HumanPlayer reads input from keyboard.</li>
    <li>a Timekeeper class, which keeps track of time for the game and stops it if the time allocated reaches 0</li>
    <li>a GameShell class, which mainly runs the game with different configurations: human vs computer or computer only.</li>
    <li>besides those classes, I have implemented a <em>wait-notify</em> approach for the game. Each player must wait for their turn!</li>
    <li>also, I have added the ability to calculate a score based on the tokens the respective player had selected.</li>
</ul>