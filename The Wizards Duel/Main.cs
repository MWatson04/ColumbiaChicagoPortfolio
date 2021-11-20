using System;
using System.Collections.Generic;

namespace WizardGameCCP
{
    // Class made to define a user controlled wizard
    class DestructionWizard
    {
        // Variables that define the wizards name, its respective spells, and its number of spell slots
        public string destructionName = "Alatar";
        public string[] destructionSpells = {"firebolt", "snowball", "shock", "windblast", "heal"};
        public int destructionSpellSlots = 6;
    
        // Allows player to restore their spell slots and accounts for any errors      
        public void DestructionMeditate()
        {
            if (destructionSpellSlots < 4)
            {
                destructionSpellSlots += 3;
                Console.WriteLine("\n" + destructionName + " is meditating.\nAlatars spell slots have gone up to " + destructionSpellSlots);
            } 
            else if (destructionSpellSlots == 6)
            {
                Console.WriteLine("\nYou are at max spell slots. You can't meditate.");
            } 
            else if (destructionSpellSlots > 4 && destructionSpellSlots < 6)
            {
                Console.WriteLine("\nYou cannot meditate past 6 spell slots.");
                Console.WriteLine("Alatar can only meditate if they are below 4 spell slots");
            }
        }

        // NOTE: The functionality of this method applies to the rest of the methods below in this class, but
        // they all have different names.
        // This method is a spell that a user can attack another wizard with to deal damage.
        // The method also stores the new amount of spell slots the player actually has after using the method.
        public void Firebolt()
        {
            Console.WriteLine("\n" + destructionName + " uses firebolt for 15 damage");
            Console.WriteLine("-2 Spell Slot");
            destructionSpellSlots -= 2;
            Console.WriteLine("You have " + destructionSpellSlots + " spell slots left\n");
        }

        public void Snowball()
        {
            Console.WriteLine("\n" + destructionName + " uses snowball for 10 damage");
            Console.WriteLine("-1 Spell Slot");
            destructionSpellSlots -= 1;
            Console.WriteLine("You have " + destructionSpellSlots + " spell slots left\n");
        }

        public void Shock()
        {
            Console.WriteLine("\n" + destructionName + " uses shock for 5 damage");
            Console.WriteLine("-0 Spell Slot");
            destructionSpellSlots -= 0;
            Console.WriteLine("You have " + destructionSpellSlots + " spell slots left\n"); 
        }

        public void Windblast()
        {
            Console.WriteLine("\n" + destructionName + " uses windblast for 10 damage");
            Console.WriteLine("-1 Spell Slot");
            destructionSpellSlots -= 1;
            Console.WriteLine("You have " + destructionSpellSlots + " spell slots left\n");
        }
    }
   
    // Class made to define a user controlled wizard
    class HealingWizard
    {
        // Variables that define the wizards name, its respective spells, and its number of spell slots
        public string healingName = "Ozir";
        public string[] healingSpells = {"heal", "divine", "holynova", "deathstrike"};
        public int healingSpellSlots = 4;

        // Allows player to restore their spell slots and accounts for any errors  
        public void HealingMeditate()
        {
            if (healingSpellSlots < 3)
            {
                healingSpellSlots += 2;
                Console.WriteLine("\n" + healingName + " is meditating.\nOzirs spell slots have gone up to " + healingSpellSlots);
            } 
            else if (healingSpellSlots == 4)
            {
                Console.WriteLine("\nYou are at max spell slots. You can't meditate.");
            } 
            else if (healingSpellSlots == 3)
            {
                Console.WriteLine("\nYou cannot meditate past 4 spell slots.");
                Console.WriteLine("Ozir can only meditate if they are below 3 spell slots");
            }
        }
       
        // NOTE: The functionality of this method applies to the rest of the methods below in this class, but
        // they all have different names.
        // This method is a spell that a user can attack another wizard with to deal damage.
        // The method also interally stores the new amount of spell slots the player actually has after using the method.
        public void Divine()
        {
            Console.WriteLine("\n" + healingName + " uses divine for 5 damage");
            Console.WriteLine("-0 Spell Slot");
            Console.WriteLine("You have " + healingSpellSlots + " spell slots left\n");
            healingSpellSlots -= 0;
        }

        public void Holynova()
        {
            Console.WriteLine("\n" + healingName + " uses holynova for 10 damage");
            Console.WriteLine("-1 Spell Slot");
            healingSpellSlots -= 1;
            Console.WriteLine("You have " + healingSpellSlots + " spell slots left\n");
        }

        public void Deathstrike()
        {
            Console.WriteLine("\n" + healingName + " uses deathstrike for 25 damage");
            Console.WriteLine("-4 Spell Slots");
            healingSpellSlots -= healingSpellSlots;
            Console.WriteLine("You have " + healingSpellSlots + " spell slots left\n");
        }
    }
   
    class Program
    {
        static void Main(string[] args)
        {  
            // Classes assigned to variables, playerOne and playerTwo, for user control       
            DestructionWizard playerOne = new DestructionWizard();
            HealingWizard playerTwo = new HealingWizard();
           
            // Lines 132-145 are used to tell the users the very basics of the game from 
            // the most important information and rules, as well as telling the user that the game has started.
            Console.WriteLine("Welcome to the Wizard Game.");
            Console.WriteLine("\nThis is a 2 player game where you and another person play as wizards and duel to the death.");
            Console.WriteLine("Player One is the destruction wizard named Alatar.\nPlayer Two will be the healing wizard named Ozir.\n");

            Console.WriteLine("Rules of the game: ");
            Console.WriteLine("Player One starts with 6 spell slots, and Player Two starts with 4 spell slots.");
            Console.WriteLine("Casting spells uses up spell slots, but you can meditate to regain lost spell slots.");
            Console.WriteLine("Both wizards start with 100 health.");
            Console.WriteLine("Player one will go first and player two goes second.");
            Console.WriteLine("Turns will alternate, and making any move during your turn will use up that turn.");
            Console.WriteLine("To make a move during your turn, you type Attack, Heal, or Meditate.");
            Console.WriteLine("Attacking allows you to use a spell that deals damage, healing allows you to restore some of your wizards health, and meditating allows you to restore some of your wizards spell slots.");
            Console.WriteLine("\nThe game is now starting.");
            Console.WriteLine("\nBegin.");
           
            // Player one and two health variables
            int playerOneHealth = 100;
            int playerTwoHealth = 100;
            
            // Game loop
            while (playerOneHealth > 0 && playerTwoHealth > 0)
            {
                // Gets player ones initial move 
                Console.Write("\nWhat will " + playerOne.destructionName + " (player one) do: ");
                string playerOneMove = Console.ReadLine().ToLower();
                
                // Used to determine player ones move
                if (playerOneMove == "attack")
                {
                    // Variable to store the kind of attack
                    Console.Write("Type Firebolt, Snowball, Shock, or Windblast to use an attack: ");
                    string playerOneAttack = Console.ReadLine().ToLower();
                    
                    // Each spell, when used, calls their respective method and then displays info about player health
                    // Accounting for spell slots to actually use the spell is also done here
                    // This process is used for all other attacking spells that the player might use in their turn
                    if (playerOneAttack == "firebolt" && playerOne.destructionSpellSlots >= 2)
                    {
                        playerOne.Firebolt();
                        Console.WriteLine("Ozir has taken 15 damage");
                        // Used to avoid displaying a negative amount of health
                        // This is used with the same purpose in all other cases for the turn
                        playerTwoHealth = Math.Max(playerTwoHealth - 15, 0);
                        Console.WriteLine("Ozirs health is now " + playerTwoHealth);
                    } 
                    else if (playerOneAttack == "firebolt" && playerOne.destructionSpellSlots < 2)
                    {
                        Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                        Console.WriteLine("Meditate to regain spell slots.");
                    } 
                    else if (playerOneAttack == "snowball" && playerOne.destructionSpellSlots >= 1)
                    {
                        playerOne.Snowball();
                        Console.WriteLine("Ozir has taken 10 damage");
                        playerTwoHealth = Math.Max(playerTwoHealth - 10, 0);
                        Console.WriteLine("Ozirs health is now " + playerTwoHealth);
                    } 
                    else if (playerOneAttack == "snowball" && playerOne.destructionSpellSlots < 1)
                    {
                        Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                        Console.WriteLine("Meditate to regain spell slots.");
                    } 
                    else if (playerOneAttack == "shock")
                    {
                        playerOne.Shock();
                        Console.WriteLine("Ozir has taken 5 damage");
                        playerTwoHealth = Math.Max(playerTwoHealth - 5, 0);
                        Console.WriteLine("Ozirs health is now " + playerTwoHealth);
                    } 
                    else if (playerOneAttack == "windblast" && playerOne.destructionSpellSlots >= 1)
                    {
                        playerOne.Windblast();
                        Console.WriteLine("Ozir has taken 10 damage");
                        playerTwoHealth = Math.Max(playerTwoHealth - 10, 0);
                        Console.WriteLine("Ozirs health is now " + playerTwoHealth);
                    } 
                    else if (playerOneAttack == "windblast" && playerOne.destructionSpellSlots < 1)
                    {
                        Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                        Console.WriteLine("Meditate to regain spell slots.");
                    }
                    else
                    {
                        Console.WriteLine("\nUndetectable Input");
                    }
                } 
                else if (playerOneMove == "heal") 
                {
                    // Increases players health variable 
                    // Accounts for spell slots and current player health
                    if (playerOneHealth >= 91)
                    {
                        Console.WriteLine("\nYou can't heal past a wizards starting health.");
                        Console.WriteLine("Alatars starting health is 100, and your current health is " + playerOneHealth + ".");
                        playerOneHealth += 0;
                    } 
                    else if (playerOneHealth < 91)
                    {
                        if (playerOne.destructionSpellSlots >= 1)
                        {
                            Console.WriteLine("\n" + playerOne.destructionName + " is healing.\n+10 Health");
                            Console.WriteLine("-1 Spell Slot");
                            playerOne.destructionSpellSlots -= 1;
                            Console.WriteLine("You have " + playerOne.destructionSpellSlots + " spell slots left\n");
                            playerOneHealth += 10;
                            Console.WriteLine("Alatars health is now " + playerOneHealth);
                        } 
                        else if (playerOne.destructionSpellSlots < 1)
                        {
                            Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                            Console.WriteLine("Meditate to regain spell slots.");
                        }
                    }
                } 
                else if (playerOneMove == "meditate")
                {
                    // Calls Meditate method
                    playerOne.DestructionMeditate();
                } 
                else
                {
                    // Message for typos in a turn
                    Console.WriteLine("\nUndetectable Input");
                }

                if (playerTwoHealth == 0)
                {
                    // Game over statements and break from game loop
                    Console.WriteLine("\n" + playerTwo.healingName + "s health is 0. The game is over.");
                    Console.WriteLine("Player One has won.");
                    break;
                } 
                
                // Gets player twos initial move
                Console.Write("\nWhat will " + playerTwo.healingName + " (player two) do: ");
                string playerTwoMove = Console.ReadLine().ToLower();
                
                // Used to determine player twos move
                if (playerTwoMove == "attack")
                {
                    // Variable to store the kind of attack
                    Console.Write("Type Divine, Holynova, or Deathstrike to use an attack: ");
                    string playerTwoAttack = Console.ReadLine().ToLower();
                    
                    // Each spell, when used, calls their respective method and then displays info about player health
                    // Accounting for spell slots to actually use the spell is also done here
                    // This process is used for all other attacking spells that the player might use in their turn.
                    if (playerTwoAttack == "divine")
                    {
                        playerTwo.Divine();
                        Console.WriteLine("Alatar has taken 5 damage");
                        // Used to avoid displaying a negative amount of health
                        // This is used with the same purpose in all other cases for the turn
                        playerOneHealth = Math.Max(playerOneHealth - 5, 0);
                        Console.WriteLine("Alatars health is now " + playerOneHealth);
                    } 
                    else if (playerTwoAttack == "holynova" && playerTwo.healingSpellSlots >= 1)
                    {
                        playerTwo.Holynova();
                        Console.WriteLine("Alatar has taken 10 damage");
                        playerOneHealth = Math.Max(playerOneHealth - 10, 0);
                        Console.WriteLine("Alatars health is now " + playerOneHealth);
                    } 
                    else if (playerTwoAttack == "holynova" && playerTwo.healingSpellSlots < 1)
                    {
                        Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                        Console.WriteLine("Meditate to regain spell slots.");
                    } 
                    else if (playerTwoAttack == "deathstrike" && playerTwo.healingSpellSlots == 4)
                    {
                        playerTwo.Deathstrike();
                        Console.WriteLine("Alatar has taken 25 damage");
                        playerOneHealth = Math.Max(playerOneHealth - 25, 0);
                        Console.WriteLine("Alatars health is now " + playerOneHealth);
                    } 
                    else if (playerTwoAttack == "deathstrike" && playerTwo.healingSpellSlots < 4)
                    {
                        Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                        Console.WriteLine("Meditate to regain spell slots.");
                    }
                    else
                    {
                        Console.WriteLine("\nUndetectable Input");
                    }
                } 
                else if (playerTwoMove == "heal")
                {
                    // Increases players health variable 
                    // Accounts for spell slots and current player health
                    if (playerTwoHealth >= 86)
                    {
                        Console.WriteLine("\nYou can't heal past a wizards starting health.");
                        Console.WriteLine(playerTwo.healingName + "s starting health is 100, and your current health is " + playerTwoHealth + ".");
                        playerTwoHealth += 0;
                    } 
                    else if (playerTwoHealth < 86)
                    {
                        if (playerTwo.healingSpellSlots >= 2)
                        {
                            Console.WriteLine("\n" + playerTwo.healingName + " is healing.\n+15 Health");
                            Console.WriteLine("-2 Spell Slots");
                            playerTwo.healingSpellSlots -= 2;
                            Console.WriteLine("You have " + playerTwo.healingSpellSlots + " spell slots left\n");
                            playerTwoHealth += 15;
                            Console.WriteLine("Ozirs health is now " + playerTwoHealth);
                        } 
                        else if (playerTwo.healingSpellSlots < 2)
                        {
                            Console.WriteLine("\nYou don't have enoughs spell slots to use this spell.");
                            Console.WriteLine("Meditate to regain spell slots.");   
                        }
                    }
                } 
                else if (playerTwoMove == "meditate")
                {
                    // Calls Meditate method 
                    playerTwo.HealingMeditate();
                } 
                else
                {
                    // Message for typos in a turn
                    Console.WriteLine("\nUndetectable Input");
                }

                if (playerOneHealth <= 0)
                {
                    // Game over statements and break from game loop
                    Console.WriteLine("\n" + playerOne.destructionName + "s health is 0. The game is over.");
                    Console.WriteLine("Player Two has won.");
                    break;
                } 
            }

            // Wait for user input to close app
            Console.ReadKey();
        }
    }
}
