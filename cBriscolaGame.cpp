// cBriscolaGame.cpp

#include "StdAfx.h"

#include "cBriscolaGame.h"
#include "save_utility.h"
#include <time.h>

// points table. This table is to retrieve points for each cards in the pool
static int g_PointsTable[] = {/*Deck*/0, 
          /*Asso*/11, /*Due*/0, /*Tre*/10, /*Quattro*/0, /*cinque*/0, /*Sei*/0, /*Sette*/0, /*Fante*/2, /*Cavallo*/3, /*Re*/4,
          /*Asso*/11, /*Due*/0, /*Tre*/10, /*Quattro*/0, /*cinque*/0, /*Sei*/0, /*Sette*/0, /*Fante*/2, /*Cavallo*/3, /*Re*/4,
          /*Asso*/11, /*Due*/0, /*Tre*/10, /*Quattro*/0, /*cinque*/0, /*Sei*/0, /*Sette*/0, /*Fante*/2, /*Cavallo*/3, /*Re*/4,
          /*Asso*/11, /*Due*/0, /*Tre*/10, /*Quattro*/0, /*cinque*/0, /*Sei*/0, /*Sette*/0, /*Fante*/2, /*Cavallo*/3, /*Re*/4 }; 

////////////////////////////////////////////////////////////////
//   *******************      CARDSPEC CLASS ******************
////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       SetCardIndex
/*! Adjust index and seed from card index
// \param long ltmpIndex : index of 40 cards mazzo
*/
void CardSpec::SetCardIndex(long ltmpIndex)
{
    m_lIndex = ltmpIndex;
    if (m_lIndex > 0 && m_lIndex <= 10 )
      m_eSeed = BASTONI;
    else if (m_lIndex > 10 && m_lIndex <= 20 )
      m_eSeed = DENARI;
    else if (m_lIndex > 20 && m_lIndex <= 30 )
      m_eSeed = SPADE;
    else if (m_lIndex > 30 && m_lIndex <= 40 )
      m_eSeed = COPPE;
    else
      m_eSeed = UNDEF;

}

////////////////////////////////////////
//       CanStrozza
/*! Return true if the this card can strozzare the card a
// \param  CardSpec &a : card a 
// \param long *plPoints : points for the eventually strozzo
*/
bool CardSpec::CanStrozza( CardSpec &a, long *plPoints)
{
    ASSERT(plPoints != NULL);

    int p0 = g_PointsTable[m_lIndex];
    int p1 = g_PointsTable[a.m_lIndex];

    *plPoints = p0 + p1;

    if ( m_eSeed == a.m_eSeed )
    {
                            // same seed   
        if (p0 > p1)
        {
                            // can strozzo this card is bigger
            return true;
        }
        else if ( p0 == p1)
        {
                            // same points: cards are lisci
            if (m_lIndex > a.m_lIndex )
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
        else
        {
                            // played card is bigger
            return false ;                 
        }
    }
    else
    {
                            // not the same seed, impossible to strozzo
        return false;
    }
}


////////////////////////////////////////
//       CalcPoints
/*! return the points that this card make on a. a is assumed played first and Bris is the briscola 
// \param CardSpec &a : played card first
// \param long *plPoints : points made (negative mean that the first player catch it)
// \param CardSpec &Bris : briscola on this game
*/
bool CardSpec::CalcPoints(CardSpec &a, long *plPoints, CardSpec &Bris)
{
    ASSERT(plPoints != NULL);

    ASSERT(m_eSeed != UNDEF && a.m_eSeed != UNDEF);
    ASSERT(m_lIndex != NOT_VALID_INDEX && a.m_lIndex != NOT_VALID_INDEX);

    int p0 = g_PointsTable[m_lIndex];
    int p1 = g_PointsTable[a.m_lIndex];

    *plPoints = p0 + p1;

    if ( m_eSeed == a.m_eSeed )
    {
                            // same seed   
        if (p0 > p1)
        {
                            // can strozzo this card is bigger
        }
        else if ( p0 == p1)
        {
                            // same points: cards are lisci
            if (m_lIndex > a.m_lIndex )
            {
            }
            else 
            {
                *plPoints = - *plPoints;
            }
        }
        else
        {
                            // played card is bigger
            *plPoints = - *plPoints;                 
        }
    }
    else if ( m_eSeed != Bris.m_eSeed && a.m_eSeed == Bris.m_eSeed )
    {
                            // this card is not briscola, the first yes
        *plPoints = - *plPoints;
    }
    else if ( m_eSeed != Bris.m_eSeed && a.m_eSeed != Bris.m_eSeed)
    {
                            // both are not briscole and not equal : the first win
        *plPoints = - *plPoints;
    }
    else
    {
                            // this is briscola and the first not
        ASSERT(m_eSeed == Bris.m_eSeed);
    }
    return true;
}

////////////////////////////////////////////////////////////////
//  *************************  PLAYER CLASS *******************
////////////////////////////////////////////////////////////////

// Constructor
cPlayer::cPlayer()
{
    CardSpec emptyCard;
    emptyCard.m_eSeed = UNDEF;
    emptyCard.m_lIndex = 0;
    m_lScore = 0;
    m_eKind = PT_HUMAN;
    strcpy_s(m_pPlayerName,"NoName");

    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_vcHand.push_back(emptyCard);
    }
    m_vctCardsTaken.reserve(NUM_CARDS);

                            // initialize statistic
    InitPlayerStat();
}


////////////////////////////////////////
//       InitPlayerStat
/*! Initialize player statistic
*/
void cPlayer::InitPlayerStat()
{
    for (int i = 0; i < NUM_SEEDS; i++)
    {
        m_Statistic.bynStroz[i] = 2;
        m_Statistic.bynRe[i] = 1;
        m_Statistic.bynHorse[i] = 1;
        m_Statistic.bynFanti[i] = 1;
    }
    m_Statistic.lNumBrisc = 0;
    m_Statistic.lNumCarac = 0;
    m_Statistic.lNumHand = 0;
    m_Statistic.lScore = 0;
    m_Statistic.bynBriscHad = 0;
    m_Statistic.bynPointsHad = 0;
    m_Statistic.bynBriscFirstHad = 0 ;
    m_Statistic.bynBriscPointsHad = 0;
    m_Statistic.lCaracHad = 0;
    m_Statistic.lRemNumBrisc = 10;
    m_Statistic.lRemNumPoints = 120;
    m_Statistic.lInHand_nBris = 0;
    m_Statistic.lInHand_nCarac = 0;
    m_Statistic.lInHand_nLisc = 0;
}

////////////////////////////////////////
//       CalculateScore
/*! Calculate the currently score of the player
*/
long cPlayer::CalculateScore()
{
    long lNumCard = m_vctCardsTaken.size();
    ASSERT( (lNumCard %2) == 0 && lNumCard < NUM_CARDS);

    long lTempScore = 0;
    for (long i = 0; i < lNumCard; i++)
    {
        long lIndexCard = m_vctCardsTaken[i];
        ASSERT(lIndexCard >=0 && lIndexCard < NUM_CARDS);
        lTempScore += g_PointsTable[lIndexCard];
    }
    m_lScore = lTempScore;

    return m_lScore;
}


////////////////////////////////////////
//       CatchTheHand
/*! The player have taken the hand. Update the player statistic.
// \param VCT_LONG &vctHand : cards taken in this hand (2 for two player)
*/
bool cPlayer::CatchTheHand(VCT_LONG &vctHand, CardSpec &cdBriscola)
{
    int iNumTaken = vctHand.size();

    for (int i = 0; i < iNumTaken; i++)
    {
        long lCard = vctHand[i];
        m_vctCardsTaken.push_back(lCard);
                            // update statistic
        long lPoints = g_PointsTable[lCard];
        m_Statistic.lScore += lPoints;
        if (lPoints >= 10)
        {
            m_Statistic.lNumCarac ++;
        }
        long lSing1 = cdBriscola.m_lIndex / 10;
        long lSign2 = lCard / 10; 
        if ( lSing1 == lSign2 )
        {
                            // catch a briscola
            m_Statistic.lNumBrisc ++;
        }
    }
    m_Statistic.lNumHand ++;

    return true;
}


////////////////////////////////////////
//       ResetThePlayer
/*! When a new game is started, player should be reinitialized
*/
bool cPlayer::ResetThePlayer()
{
                        // clear score 
    m_lScore = 0;
    m_vctCardsTaken.clear();

    for (int j = 0; j < NUM_CARDS_HAND; j++)
    {
        m_vcHand[j].m_eSeed = UNDEF;
        m_vcHand[j].m_lIndex = NOT_VALID_INDEX; 
    }
                        // rest statistic
    InitPlayerStat();

    return true;
}


////////////////////////////////////////
//       IsHandEmpty
/*! Return true if all cards are undefined, that mean all cards in the hand are been played 
*/
bool cPlayer::IsHandEmpty()
{
    bool bRes = true;
    for (int j = 0; j < NUM_CARDS_HAND; j++)
    {
        if (m_vcHand[j].m_eSeed != UNDEF)
        {
            bRes = false;
            break;
        }
        
    }
    return bRes;
}


////////////////////////////////////////////////////////////////
// **********************   BRISCOLACORE CLASS *****************
////////////////////////////////////////////////////////////////


// Constructor
cBriscolaCore::cBriscolaCore(int iNumPlayers)
{
    TRACE("cBriscolaCore is created\n");
                            // mazzo init
    m_vctCards.reserve(NUM_CARDS);
    for (int i = 0; i < NUM_CARDS; i++)
    {
        m_vctCards.push_back(i);
    }
    m_lNextCard = 1;

                            // played cards init
    m_vctPlayedCards.reserve(iNumPlayers);

    for (int i = 0; i < iNumPlayers; i++)
    {
        m_vctPlayers.push_back(cPlayer());
    }

                            // briscola init
    m_lNumPlayers = iNumPlayers;

    m_crdOnTable.m_eSeed = UNDEF;
    m_crdOnTable.m_lIndex = NOT_VALID_INDEX;

                            // initialize also rand seed
    srand( (unsigned)time( NULL ) );

                            // game status
    m_eStatus = GAME_WAIT_FOR_NEWGAME;

                            // first player have to begin
    m_lPlayFirst = 0;
    m_lPlHaveToPlay = 0;
    m_lStartPlayer = 0;
                            // player circle init
    m_vct_PlayerCircle.reserve(iNumPlayers);    
    PLAYER_CARD_ST pairTemp;
    pairTemp.player  = 0;
    pairTemp.status  = WAITINGPLAYER_TOPLAY;
    m_vct_PlayerCircle.push_back(pairTemp);

    pairTemp.player  = 1;
    pairTemp.status  = WAITING_CPU_TOPLAY;
    m_vct_PlayerCircle.push_back(pairTemp);

    m_eGameLevel = DUMMY;
    m_pFunCPUplayer = &cBriscolaCore::CPUPlayAlwaysTheFirst;
    m_eGameType = BRISC_NORMINDUE;

    m_Match_Stat.lTotSegniLose = 0;
    m_Match_Stat.lTotSegniWons = 0;
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        m_vctPlayers[i].m_Statistic.lSegniWons = 0;
    }

    m_eOppType = CPU_TYPE;

}


////////////////////////////////////////
//       SetLevel
/*! Set a new game level
// \param eGameLevel eNewLevel : new level to be set
*/
bool  cBriscolaCore::SetLevel(eGameLevel eNewLevel)
{
    m_eGameLevel = eNewLevel;

    switch(eNewLevel)
    {
        case DUMMY:
            m_pFunCPUplayer = &cBriscolaCore::CPUPlayAlwaysTheFirst;
            break;
        case BEGINNER:
            m_pFunCPUplayer = &cBriscolaCore::CPUPlayBegginner;
            break;

        case ADVANCED:
            m_pFunCPUplayer = &cBriscolaCore::CPUPlayAdvanced;
            break;

        case NIGHTMARE:
            break;

        default:
            ASSERT(0);

    }
    

    return true;
}


////////////////////////////////////////
//       WhoWinTheGame
/*! Return the player index who wons the game. If the game is drawn pbIsDrawn is set to true.
// \param long* plPlayerIx : return winner index
// \param bool* pbIsDrawn : return true if the game has no winner, otherwise false
*/
bool  cBriscolaCore::WhoWinTheGame(long* plPlayerIx, bool* pbIsDrawn)
{
    m_eStatus = NOT_READY_TO_PLAY;
    TRACE("WhoWinTheGame()\n");

    if (plPlayerIx == NULL || plPlayerIx == NULL )
    {
        return false;
    }

    long lScore;
    long lMaxScore = -10;
    long lTotalSum = 0;
  
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        lScore = m_vctPlayers[i].CalculateScore();
        if (lScore > lMaxScore)
        {
            *pbIsDrawn = false;
            lMaxScore = lScore;
            *plPlayerIx = i;
        }
        else if (lScore == lMaxScore)
        {
            *pbIsDrawn = true;
        }
        lTotalSum += lScore;
    }

    

    ASSERT(lTotalSum == TOTAL_POINTS);

    return true;
}


////////////////////////////////////////
//       InitNewMatch
/*! new match the best of 4 segni, reset match statistic
*/
void  cBriscolaCore::InitNewMatch()
{
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        m_vctPlayers[i].m_Statistic.lSegniWons = 0;
    }
    
    
}


////////////////////////////////////////
//       SetFirstPlayer
/*! Set the player that play at first
// \param long lIndexPl : index of player
*/
bool cBriscolaCore::SetFirstPlayer(long lIndexPl)
{
    m_eStatus = NOT_READY_TO_PLAY; 

    m_lPlayFirst = lIndexPl;

                            // make circle player
    MakePlayerCircle();

                             // game status from player that is first
    m_eStatus = WAIT_FOR_MAZZO;

    return true;
}


////////////////////////////////////////
//       InitPlayWithMazzo
/*! Init the game with mazzo
// \param VCT_LONG &vct_Mazzo : 
// \param eGameType eType : 
*/
bool cBriscolaCore::InitPlayWithMazzo(VCT_LONG& vct_Mazzo, eGameType eType)
{
    TRACE("InitPlayWithMazzo()\n");
    ASSERT( m_eStatus == WAIT_FOR_MAZZO);

    m_eStatus = NOT_READY_TO_PLAY;

                            // clear card played
    m_vctPlayedCards.clear();

                            // reset to the first card on pool
    m_lNextCard = 1;
      
    m_vctCards = vct_Mazzo;
    Utility::TraceContainer(m_vctCards, "Cards mazzo"); 
   
    CardSpec tmpCard;
    bool bMore;
    long lIndex;
                            // initialize all players
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        int iPlayerIx = m_vct_PlayerCircle[i].player;
        ASSERT(iPlayerIx >= 0 && iPlayerIx < m_lNumPlayers);
                             // rest the player information, before begin
        m_vctPlayers[iPlayerIx].ResetThePlayer();

                            // note the order. Cards are distribueted first to the player that must begin
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
                                // player get the card
            lIndex = GetNextCard(&bMore);
            ASSERT(bMore);

            tmpCard.SetCardIndex(lIndex);

            m_vctPlayers[iPlayerIx].m_vcHand[j] = tmpCard;
        }
    }

    Utility::TraceContainer(m_vctPlayers, "Player status");

                            // Make the briscola
    lIndex = ThrowTableCard();
    tmpCard.SetCardIndex(lIndex);
    m_crdOnTable = tmpCard;

                             // circle must already defined with SetFirstPlayer
    m_eStatus = m_vct_PlayerCircle[0].status;

    TRACE("In tavola %d\n", lIndex);

    return true;
}


////////////////////////////////////////
//       InitPlay
/*! Make all stuff to initialize the game such shuffle the cards, reset player information 
    and distribuite the cards for the first hand 
// \param long lIndexPl : Player index that must begin the play
// \param eGameType eType : type of the game (scoperta or standard)
*/
bool cBriscolaCore::InitPlay(long lIndexPl, eGameType eType)
{
    TRACE("InitPlay()\n");

    IT_VCTLONG it_tmp;

    ASSERT(lIndexPl >= 0 && lIndexPl < m_lNumPlayers);
    m_eStatus = NOT_READY_TO_PLAY;


    m_lPlayFirst = lIndexPl;

                            // make circle player
    MakePlayerCircle();

                            // game status from player that is first
    m_eStatus = m_vct_PlayerCircle[0].status;

                            // clear card played
    m_vctPlayedCards.clear();

                            // reset to the first card on pool
    m_lNextCard = 1;
      
    it_tmp = m_vctCards.begin();
                            // Leave the deck card to the first position
    it_tmp++;

                            // use the rand() function to shuffle the pool (deck is not shuffled)
    std::random_shuffle(it_tmp, m_vctCards.end());
    ASSERT(m_vctCards[0] == 0);

    m_vctStartCards.clear();
    Utility::TraceContainer(m_vctCards, "Cards mazzo"); 
                            // store data for remote  session
    m_vctStartCards = m_vctCards;
    m_lStartPlayer = lIndexPl;

    CardSpec tmpCard;
    bool bMore;
    long lIndex;

                            // initialize all players
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        int iPlayerIx = m_vct_PlayerCircle[i].player;
        ASSERT(iPlayerIx >= 0 && iPlayerIx < m_lNumPlayers);

                            // rest the player information, before begin
        m_vctPlayers[iPlayerIx].ResetThePlayer();
                            // get the first hand to each player
                            // distribuite the cards first to the player that have to start
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
            lIndex = GetNextCard(&bMore);
            tmpCard.SetCardIndex(lIndex);

            m_vctPlayers[iPlayerIx].m_vcHand[j] = tmpCard;
        }
    }

    Utility::TraceContainer(m_vctPlayers, "Player status");

                            // Make the briscola
    lIndex = ThrowTableCard();
    tmpCard.SetCardIndex(lIndex);
    m_crdOnTable = tmpCard;
    TRACE("In tavola %d\n", lIndex);

    return true;
}


////////////////////////////////////////
//       GetPlayerInPlaing
/*! Return the index of the player that must play
// \param long * plPlayerIx : 
*/
bool  cBriscolaCore::GetPlayerInPlaing(long * plPlayerIx)
{
    if (plPlayerIx == NULL)
        return false;

    *plPlayerIx = m_lPlHaveToPlay;

    return true;
}


////////////////////////////////////////
//       GetStatus
/*! Return the game status 
// \param eBriscolaStatus* pSt : returned status 
*/
bool  cBriscolaCore::GetStatus(eBriscolaStatus* pSt)
{
    if (pSt == NULL)
        return false;

    *pSt = m_eStatus;
    
    return true;
}


////////////////////////////////////////
//       CardIsPlayed
/*! A player have played a card, terminate a hand or the game or simply wait for the next
// \param int iPlayerIx : player index
// \param int iHandIx : hand card index
*/
bool  cBriscolaCore::CardIsPlayed(int iPlayerIx, int iHandIx)
{
    TRACE("CardIsPlayed()\n");
    if (m_eStatus != WAITINGPLAYER_TOPLAY &&
        m_eStatus != WAITINGPLAYER_2_TOPLAY &&
        m_eStatus != WAITING_CPU_TOPLAY && 
        m_eStatus != NOT_READY_TO_PLAY)
    {
        ASSERT(0);
        return false;
    }
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers 
         || iHandIx < 0 || iHandIx > NUM_CARDS_HAND )
    {
        ASSERT(0);
        return false;
    }
    m_eStatus = NOT_READY_TO_PLAY;


    CardSpec Card = m_vctPlayers[iPlayerIx].m_vcHand[iHandIx];

    m_vctPlayers[iPlayerIx].m_vcHand[iHandIx].m_lIndex = NOT_VALID_INDEX;
    m_vctPlayers[iPlayerIx].m_vcHand[iHandIx].m_eSeed = UNDEF;

                            // store the played card
    PAIR_PLAYER_CARD prPlayed(iPlayerIx, Card);
    m_vctPlayedCards.push_back(prPlayed);

                            // if all players have played, retrive who catch the hand
    long lNumCardPlayed = m_vctPlayedCards.size();
    if (lNumCardPlayed >= m_lNumPlayers)
    {
                            // ------- hand is terminated ------------
                            // update statistic
        UpdateStatistic(); 
                            // get the score
        WhoWinTheHand();
        m_vctPlayedCards.clear();
                            // control if the the game is finished
        bool bFinish = true;
        if (m_lNextCard < NUM_CARDS)
        {
                            // there are more cards on mazzo: play is not finished 
            bFinish = false;
        }
        else
        {
                            // no more cards on the mazzo, look on players hand
            for (int i = 0; i < m_lNumPlayers; i++ )
            {
                if (!m_vctPlayers[iPlayerIx].IsHandEmpty())
                {
                    bFinish = false;
                    break;
                }
            }
        }
        if (bFinish)
        {
                            // all players have played all cards and no more cards are on mazzo
                            // change the status
            long lPlayerIx = 0;
            bool bdraw = false;

            WhoWinTheGame(&lPlayerIx, &bdraw); 

            if (bdraw)
            {
                m_eStatus = SEGNO_TERMINATED;
            }
            else
            {
                m_vctPlayers[lPlayerIx].m_Statistic.lSegniWons ++;
                ASSERT(m_vctPlayers[lPlayerIx].m_Statistic.lSegniWons <= SEGNI_ON_MATCH );
                if ( m_vctPlayers[lPlayerIx].m_Statistic.lSegniWons >= SEGNI_ON_MATCH )
                {
                    m_eStatus = GAME_TERMINATED;   
                }
                else
                {
                    m_eStatus = SEGNO_TERMINATED;
                }
            }

        }
        else
        {
                            // hand is terminated
            m_eStatus = HAND_TERMINATED;
        }
          
    }
    else
    {
                            // ------- hand is not terminate: waiting play of the next player --------
        m_lPlHaveToPlay ++;
        ASSERT(m_lPlHaveToPlay >= 0 && m_lPlHaveToPlay < m_lNumPlayers);
        m_eStatus = m_vct_PlayerCircle[m_lPlHaveToPlay].status;       

    }

    TRACE("Status: %d\n",m_eStatus);
    return true;
}



////////////////////////////////////////
//       PlayerAbortTheSegno
/*! Player abort the current segno
// \param long lAbortPlayerIndey : index of the player the t abort the sgno
// \return true if the the game is terminated
*/
BOOL cBriscolaCore::PlayerAbortTheSegno(long lAbortPlayerIndey, BOOL bMazzo)
{
    long lPlayerIx;
    BOOL bRes = FALSE;

    if ( lAbortPlayerIndey == 0)
        lPlayerIx = 1;
    else
        lPlayerIx = 0;
       
    eBriscolaStatus eOldStatus = m_eStatus;
    
    m_vctPlayers[lPlayerIx].m_Statistic.lSegniWons ++;
    ASSERT(m_vctPlayers[lPlayerIx].m_Statistic.lSegniWons <= SEGNI_ON_MATCH );
    if ( m_vctPlayers[lPlayerIx].m_Statistic.lSegniWons >= SEGNI_ON_MATCH )
    {
        if ( bMazzo )
        {
                            // mazzo is already received, that mean a new game is started
            InitNewMatch();
            m_eStatus = eOldStatus;
        }
        else
        {
            m_eStatus = GAME_WAIT_FOR_NEWGAME; 
        }
        bRes = TRUE;
    }
    else
    {
        if ( m_eOppType == CPU_TYPE)
        {
            m_eStatus = NEW_SEGNO;
        }
        else
        {
            if ( bMazzo )
            {
                m_eStatus = eOldStatus;
            }
            else
            {
                m_eStatus = NEW_NET_SEGNO;
            }
        }
        
    }
    return bRes;
}


////////////////////////////////////////
//       UpdateStatistic
/*! hand is terminated update the game statistic
*/
void cBriscolaCore::UpdateStatistic()
{
    int iNumCardPlayed = m_vctPlayedCards.size();
    bool bIsTheFirstHand = false;

    if ( m_vctPlayers[0].m_Statistic.lNumHand == 0 &&
         m_vctPlayers[1].m_Statistic.lNumHand == 0)
    {
        bIsTheFirstHand = true;
    }

                            // iterate card played
    for (int i = 0; i < iNumCardPlayed; i++)
    {
        CardSpec Card = m_vctPlayedCards[i].second;
        long lPlayerIndex = m_vctPlayedCards[i].first;
        long lPoints = g_PointsTable[Card.m_lIndex];
        if (lPoints >= 10)
        {
                            // Stroz remained are fewer
                            // update info for both
            m_vctPlayers[0].m_Statistic.bynStroz[Card.m_eSeed] --;
            m_vctPlayers[1].m_Statistic.bynStroz[Card.m_eSeed] --;
            ASSERT(m_vctPlayers[0].m_Statistic.bynStroz[Card.m_eSeed] >= 0);
      
            m_vctPlayers[lPlayerIndex].m_Statistic.lCaracHad ++;
        }
        else if ( lPoints == 4)
        {
                            // card played was a King
            m_vctPlayers[0].m_Statistic.bynRe[Card.m_eSeed] --;
            m_vctPlayers[1].m_Statistic.bynRe[Card.m_eSeed] --;
            ASSERT(m_vctPlayers[0].m_Statistic.bynRe[Card.m_eSeed] >= 0);

        }
        else if ( lPoints == 3)
        {
                            // card played was a horse
            m_vctPlayers[0].m_Statistic.bynHorse[Card.m_eSeed] --;
            m_vctPlayers[1].m_Statistic.bynHorse[Card.m_eSeed] --;
            ASSERT(m_vctPlayers[0].m_Statistic.bynHorse[Card.m_eSeed] >= 0);
        }
        else if (lPoints == 2)
        {
                            // card played was a fante
            m_vctPlayers[0].m_Statistic.bynFanti[Card.m_eSeed] --;
            m_vctPlayers[1].m_Statistic.bynFanti[Card.m_eSeed] --;
            ASSERT(m_vctPlayers[0].m_Statistic.bynFanti[Card.m_eSeed] >= 0);
        }

        if (i == 0)
        {
                            // first card played
            m_vctPlayers[lPlayerIndex].m_Statistic.eLastPlayed = Card.m_eSeed;
        }
                            // control briscola played
        if (Card.m_eSeed == m_crdOnTable.m_eSeed )
        {
            m_vctPlayers[lPlayerIndex].m_Statistic.bynBriscHad ++;
            if (bIsTheFirstHand)
            {
                m_vctPlayers[lPlayerIndex].m_Statistic.bynBriscFirstHad ++;
            }
            m_vctPlayers[lPlayerIndex].m_Statistic.bynBriscPointsHad += lPoints;
                            // decrement briscole count
            m_vctPlayers[0].m_Statistic.lRemNumBrisc --;
            m_vctPlayers[1].m_Statistic.lRemNumBrisc --;
            ASSERT( m_vctPlayers[0].m_Statistic.lRemNumBrisc >= 0 &&
                    m_vctPlayers[1].m_Statistic.lRemNumBrisc >= 0);
                   
        }    
                            // points played
        m_vctPlayers[lPlayerIndex].m_Statistic.bynPointsHad += lPoints;
                            // remaineded points
        m_vctPlayers[0].m_Statistic.lRemNumPoints -= lPoints;
        m_vctPlayers[1].m_Statistic.lRemNumPoints -= lPoints;

    }
                        // complete first hand stat
    if (bIsTheFirstHand)
    {
                        // this the first hand
        for (unsigned int i = 0; i < m_vctPlayers.size(); i++)
        {
            for (unsigned int j = 0; j < NUM_CARDS_HAND; j++)
            {
                CardSpec Card1 = m_vctPlayers[i].m_vcHand[j];
                if ( Card1.m_eSeed == m_crdOnTable.m_eSeed )
                {
                    m_vctPlayers[i].m_Statistic.bynBriscFirstHad ++;
                }
            }
        }
    }
}


////////////////////////////////////////
//       UpdateStatWithHand
/*! Update statistic with cards in the hand
*/
void  cBriscolaCore::UpdateStatWithHand(int iPlayerIx)
{
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers )
    {
        ASSERT(0);
        return;
    }
                            // reference to statistic
    PLAYER_STATISTIC& Stat = m_vctPlayers[iPlayerIx].m_Statistic;

    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        CardSpec Card = m_vctPlayers[iPlayerIx].m_vcHand[i];
        long lPoints = g_PointsTable[Card.m_lIndex];

        if (lPoints >= 10)
        {
                            // Stroz remained are fewer
            Stat.bynStroz[Card.m_eSeed] --;            
        }
        else if ( lPoints == 4)
        {
                            // card played was a King
            Stat.bynRe[Card.m_eSeed] --;

        }
        else if ( lPoints == 3)
        {
                            // card played was a horse
            Stat.bynHorse[Card.m_eSeed] --;
        }
        else if (lPoints == 2)
        {
                            // card played was a fante
            Stat.bynFanti[Card.m_eSeed] --;
        }
        if ( Card.m_eSeed = m_crdOnTable.m_eSeed )
        {
                            // card is briscola
            Stat.lRemNumBrisc--;
            ASSERT(Stat.lRemNumBrisc >= 0);
        }
                            // points remained
        Stat.lRemNumPoints -= lPoints;
        ASSERT(Stat.lRemNumPoints >= 0);
        
    }
}

////////////////////////////////////////
//       PlayACardDad
/*! The class is invited to play a card in a intelligent manner
// \param int iPlayerIx : player that the card have to play
// \param long* plPlayedCard : returned played card index
// \param lPosHand:
*/
bool cBriscolaCore::PlayACardDad(int iPlayerIx, long* plPlayedCard, long* plPosHand)
{
    TRACE("PlayACardDad()\n");
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers || plPlayedCard == NULL
         || plPosHand == NULL)
    {
        ASSERT(0);
        return false;
    }

    m_eStatus = NOT_READY_TO_PLAY;
    
                            // play always the first (a genius!)
    *plPlayedCard = NOT_VALID_INDEX;
    

                            // call the function to dice a card
    (this->*m_pFunCPUplayer)(iPlayerIx, plPlayedCard, plPosHand);

                             // update the table 
    if (*plPlayedCard != NOT_VALID_INDEX)
    {
        ASSERT(*plPosHand > -1);
        CardIsPlayed(iPlayerIx, *plPosHand);
    }
    else
    {
                            // no card in cpu hand to play, game is terminated
        m_eStatus = GAME_TERMINATED;
                            // assertion because beacuse game termination should be cacthed in other place
        ASSERT(0);
        return false;
    }

    return true;
}


////////////////////////////////////////
//       CPUPlayAlwaysTheFirst
/*! CPU play the first card (very, very dummy stratagey)
// \param int iPlayerIx : player index that must play
// \param long* plPlayedCard : card index to be played
// \param long* plPosHand : card position on player hand
*/
bool cBriscolaCore::CPUPlayAlwaysTheFirst(int iPlayerIx, long* plPlayedCard, long* plPosHand)
{
    int iHandIx = 0;

    while (*plPlayedCard == NOT_VALID_INDEX && iHandIx < NUM_CARDS_HAND)
    {
        *plPlayedCard = m_vctPlayers[iPlayerIx].m_vcHand[iHandIx].m_lIndex;
        iHandIx++;
       
    }
    
    iHandIx--;

    *plPosHand = iHandIx;

    return true;
}


////////////////////////////////////////
//       CPUPlayAdvanced
/*! Advanced player. Used a top strategy system based on card evaluation.
//  Single card evaluation is base on fuzzy rules that sintetyzer a top player expertize.
// \param int iPlayerIx : player index that must play
// \param long* plPlayedCard : returned card index to be played
// \param long* plPosHand : returned card position on player hand
*/
bool cBriscolaCore::CPUPlayAdvanced(int iPlayerIx, long* plPlayedCard, long* plPosHand)
{
    bool bIamTheFirst = (m_vctPlayedCards.size() == 0);

    VCT_LONG vPoints(NUM_CARDS_HAND);

                            // update the statistic with card in hand
    UpdateStatWithHand(iPlayerIx);

    if (bIamTheFirst)
    {
                            // cpu (or authomatic player) is first
        CalcAdvFirstPoints(iPlayerIx, vPoints);
        Utility::TraceContainer(vPoints, "Points if CPU start");
    }
    else
    {
                            // cpu (or authomatic player) is second
        CardSpec crdPlayed = m_vctPlayedCards[0].second;

                            // calculate points for each card in the hand        
        CalcAdvSecondPoints(crdPlayed, iPlayerIx, vPoints);

        Utility::TraceContainer(vPoints, "Points if CPU catch");
    }

                            //  play the card that made the max points
    int iMaxIndex = 0;
    int iMaxPoints = vPoints[0];
    for (int i = 1; i < NUM_CARDS_HAND; i++ )
    {
        if ( vPoints[i] > iMaxPoints)
        {
            iMaxIndex = i;
            iMaxPoints = vPoints[i];
        }
    }
    ASSERT(iMaxPoints > -121);
    *plPlayedCard = m_vctPlayers[iPlayerIx].m_vcHand[iMaxIndex].m_lIndex;
    *plPosHand = iMaxIndex;
    ASSERT(*plPlayedCard != NOT_VALID_INDEX);
    
    return true;
}


////////////////////////////////////////
//       CalcAdvFirstPoints
/*! Level advanced: play as first calculation values
// \param int iPlayerIx : player index
// \param VCT_LONG &vPoints : vector of points
*/
bool cBriscolaCore::CalcAdvFirstPoints(int iPlayerIx, VCT_LONG &vPoints)
{
                            // matrix of possibilities
    Matrix::cUserMatrix mtxVal(5, NUM_CARDS_HAND);
    
    CardSpec Card;
    long lPoints;
    eSEED eBrisc = m_crdOnTable.m_eSeed;

    PLAYER_STATISTIC& Stat = m_vctPlayers[iPlayerIx].m_Statistic;
    int iPlayerIx_opp = iPlayerIx == 0 ? 1: 0;
    PLAYER_STATISTIC& Stat_opp = m_vctPlayers[iPlayerIx_opp].m_Statistic; 
    
    int iNumHandPlayed = Stat.lNumHand + Stat_opp.lNumHand;
    int iNumHandRemained = 20 - iNumHandPlayed;

    // row 0 is penalty due to stroz on opponent

    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        Card = m_vctPlayers[iPlayerIx].m_vcHand[i];
        lPoints = g_PointsTable[Card.m_lIndex];
        if (Card.m_eSeed == eBrisc )
        {
                            // card is briscola
            if (lPoints >= 10)
            {
                            // big briscola
                mtxVal[3][i] = -1000 + lPoints;
            }
            
        }
        else if (lPoints >= 10)
        {
                             // general penalize to playing a carac
            mtxVal[2][i] = - lPoints;
        }
        else if (lPoints == 2)
        {
                            // card is fante
            mtxVal[0][i] =  - 10 * ( Stat.bynHorse[Card.m_eSeed] + 3 * Stat.bynRe[Card.m_eSeed] + 
                                     5 * Stat.bynStroz[Card.m_eSeed] ); 
                            
        }
        else if (lPoints == 3)
        {
                            // card is horse
            mtxVal[0][i] =  - 10 * ( 4 * Stat.bynRe[Card.m_eSeed] + 6 * Stat.bynStroz[Card.m_eSeed] ); 
                            
        }
        else if (lPoints == 4)
        {
                            // card is king
            mtxVal[0][i] =  - 10 * ( 7 * Stat.bynStroz[Card.m_eSeed] ); 
                            
        }
        else
        {
                            // card is liscio and not briscola
                            // set a penalty if the opponent could catch with strozzo
            mtxVal[0][i] =  - 10 * Stat.bynStroz[Card.m_eSeed]; 
        }
        if (lPoints == 10)
        {
                            // card is 3
                            // never play a 3 if a 1 could be present on opponent hand
            if (Stat.bynStroz[Card.m_eSeed] == 2)
            {
                            // opponent could have a ass to catch the 3
                mtxVal[1][i] = -1000;
            }
        }
    }
    Utility::TraceItem( mtxVal, "Fuzzy Matrix") ;
    

    return true;
}


////////////////////////////////////////
//       CalcAdvSecondPoints
/*! Level advanced: play as second values calculation
// \param CardSpec &crdPlayed : card played
// \param int iPlayerIx : player index
// \param VCT_LONG &vctlPoints : vector of points
*/
bool cBriscolaCore::CalcAdvSecondPoints(CardSpec &crdPlayed, int iPlayerIx, VCT_LONG &vctlPoints)
{
    return true;
}

////////////////////////////////////////
//       CPUPlayBegginner
/*! At the begginner algorithm is easy. Rules as defined and respected without exceptions.
// \param int iPlayerIx : 
// \param long* plPlayedCard : 
// \param long* plPosHand : 
*/
bool cBriscolaCore::CPUPlayBegginner(int iPlayerIx, long* plPlayedCard, long* plPosHand)
{

    bool bIamTheFirst = (m_vctPlayedCards.size() == 0);

    VCT_LONG vPoints(NUM_CARDS_HAND);

    if (bIamTheFirst)
    {
                            // cpu is first
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
            CardSpec crdTmp = m_vctPlayers[iPlayerIx].m_vcHand[j];
            long lPoints;

            if (crdTmp.m_eSeed != UNDEF)
            {
                lPoints = - g_PointsTable[crdTmp.m_lIndex ];
                if (crdTmp.m_eSeed  == m_crdOnTable.m_eSeed)
                {
                            // this is briscola, not to play
                    lPoints -= 5 ;
                }
            }
            else
            {
                lPoints = -121;
            }
            vPoints[j] = lPoints;

        }
        Utility::TraceContainer(vPoints, "Points if CPU start");
    }
    else
    {
                            // cpu is second
        CardSpec crdPlayed = m_vctPlayedCards[0].second;

                            // calculate points for each card in the hand        
        CalcHandPoints(crdPlayed, iPlayerIx, vPoints);

        Utility::TraceContainer(vPoints, "Points if CPU catch");
    }

                            // beginner play the card that made the max points
    int iMaxIndex = 0;
    int iMaxPoints = vPoints[0];
    for (int i = 1; i < NUM_CARDS_HAND; i++ )
    {
        if ( vPoints[i] > iMaxPoints)
        {
            iMaxIndex = i;
            iMaxPoints = vPoints[i];
        }
    }
    ASSERT(iMaxPoints > -121);
    *plPlayedCard = m_vctPlayers[iPlayerIx].m_vcHand[iMaxIndex].m_lIndex;
    *plPosHand = iMaxIndex;
    ASSERT(*plPlayedCard != NOT_VALID_INDEX);
    
    return true;
}


////////////////////////////////////////
//       CanIStroz
/*! Control if strozzo is possible for the player and collect points for each possible card.
// \param CardSpec &crdPlayed : card already played
// \param int iPlayerIx : player index
// \param long* plPosHand : retuned card position that make a strozzo
*/
bool cBriscolaCore::CanIStroz(CardSpec &crdPlayed, int iPlayerIx, long* plPosHand, VCT_LONG &vctlPoints)
{
    CardSpec crdTmp;
    bool bRes = false;

    for (int iHandIx = 0; iHandIx < NUM_CARDS_HAND; iHandIx++)
    {
        crdTmp = m_vctPlayers[iPlayerIx].m_vcHand[iHandIx];
        long lPoints;

        if ( crdTmp.CanStrozza(crdPlayed, &lPoints)  )
        {
            bRes = true;
        }
        vctlPoints[iHandIx] = lPoints;
    }

    return bRes;
}


////////////////////////////////////////
//       CalcHandPoints
/*! A card was played, explore all possibilities to play
// \param CardSpec &crdPlayed : card played
// \param int iPlayerIx : player index
// \param VCT_LONG &vctlPoints : vecto of calculated points 
*/
bool  cBriscolaCore::CalcHandPoints(CardSpec &crdPlayed, int iPlayerIx, VCT_LONG &vctlPoints)
{
    CardSpec crdTmp;
    bool bRes = false;

    for (int iHandIx = 0; iHandIx < NUM_CARDS_HAND; iHandIx++)
    {
        crdTmp = m_vctPlayers[iPlayerIx].m_vcHand[iHandIx];
        long lPoints;

        if (crdTmp.m_eSeed != UNDEF)
        {
            crdTmp.CalcPoints(crdPlayed, &lPoints, m_crdOnTable);
        }
        else
        {
            lPoints = -121;
        }
   
        vctlPoints[iHandIx] = lPoints;
    }

    return true;
}


////////////////////////////////////////
//       GetPlayerScore
/*! Return the curenntly player score
// \param int iPlayerIx : index player
// \param long *plScore : pointer to the returned score
*/
bool cBriscolaCore::GetPlayerScore(int iPlayerIx, long *plScore)
{
    
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers || plScore == NULL)
    {
        if (plScore != NULL)
            *plScore = 0;

        ASSERT(0);
        return false;
    }
    *plScore = m_vctPlayers[iPlayerIx].CalculateScore();

    return true;
}


////////////////////////////////////////
//       GetSegniScore
/*! Segni of the player
// \param int iPlayerIx : 
// \param long *plScore : 
*/
bool cBriscolaCore::GetSegniScore(int iPlayerIx, long *plScore)
{
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers || plScore == NULL)
    {
        if (plScore != NULL)
            *plScore = 0;

        ASSERT(0);
        return false;
    }
    *plScore = m_vctPlayers[iPlayerIx].m_Statistic.lSegniWons;

    return true;
}

////////////////////////////////////////
//       GetCardInHand
/*! Return a card index on player hand 
// \param long* plIndex : returned index value
// \param int iPlayerIx : player index
// \param int iHandIx : hand index
*/
bool  cBriscolaCore::GetCardInHand(int iPlayerIx, int iHandIx, long* plIndex)
{
    
    *plIndex = 0;
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers 
         || iHandIx < 0 || iHandIx > NUM_CARDS_HAND ||
         plIndex == NULL )
    {
        ASSERT(0);
        return false;
    }

    *plIndex = m_vctPlayers[iPlayerIx].m_vcHand[iHandIx].m_lIndex;

    return true;
}


////////////////////////////////////////
//       SetPlayerRemote
/*! Set the type of player
// \param  int iPlayerIx : 
// \param eTypeOfPLayer eType : 
*/
bool cBriscolaCore::SetPlayerRemote( int iPlayerIx, eTypeOfPLayer eType)
{
    if ( iPlayerIx < 0 || iPlayerIx >= m_lNumPlayers )
    {
        ASSERT(0);
        return false;
    }
    m_vctPlayers[iPlayerIx].m_eKind = eType;

    return true;
}

////////////////////////////////////////
//       StatusByIndexPlayer
/*! return a wating status on player index
// \param int iPlayerIndex : 
*/
eBriscolaStatus cBriscolaCore::StatusByIndexPlayer(int iPlayerIndex)
{
    eBriscolaStatus eTemp = FAULT;
    ASSERT(iPlayerIndex >= 0 && iPlayerIndex < m_lNumPlayers);
    switch (iPlayerIndex)
    {
        case 0:
            eTemp = WAITINGPLAYER_TOPLAY;
            break;
        case 1:
            if (m_vctPlayers[iPlayerIndex].m_eKind == PT_REMOTE )
            {
                eTemp = WAITINGPLAYER_2_TOPLAY;
            }
            else
            {
                eTemp = WAITING_CPU_TOPLAY;
            }
            break;
        default:
            ASSERT(0);
    }
    return eTemp;
}

////////////////////////////////////////
//       MakePlayerCircle
/*! Fill the vector with the player queue
// \param VCT_LONG &vct_PlayerCircle : 
*/
bool cBriscolaCore::MakePlayerCircle()
{
    TRACE("MakePlayerCircle()\n");
    int j = 0;
    for (int i = m_lPlayFirst; i < m_lNumPlayers; i++)
    {
        m_vct_PlayerCircle[j].player = i;
        
        m_vct_PlayerCircle[j].status = StatusByIndexPlayer(i);;
        j++;
    }
    for (int i = 0; i < m_lPlayFirst; i++)
    {
        m_vct_PlayerCircle[j].player = i;
        m_vct_PlayerCircle[j].status = StatusByIndexPlayer(i);
        j++;
    }

    m_lPlHaveToPlay = 0;

    return true;
}

////////////////////////////////////////
//       BeginNewHand
/*! A Hand is done and players throw a new card.
*/
bool  cBriscolaCore::BeginNewHand()
{
    ASSERT(m_eStatus == HAND_TERMINATED);
    TRACE("BeginNewHand()\n");

    m_eStatus = NOT_READY_TO_PLAY;

                            // make order for getting the new card
    MakePlayerCircle();

                            // set the new status
    m_eStatus = m_vct_PlayerCircle[0].status;
    
                            // are there still card to get?
    if (m_lNextCard >= NUM_CARDS )
    {
                            // no more cards to get
       return false; 
    }

    bool bRes;

    CardSpec tmpCard;


    Utility::TraceContainer(m_vctPlayers, "Player status before new hand");

    for (int i = 0; i < m_lNumPlayers; i++)
    {
                            // player get the card
        long lIndex = GetNextCard(&bRes);
        ASSERT(bRes);

        tmpCard.SetCardIndex(lIndex);
		int j;
        for (j = 0; j < NUM_CARDS_HAND; j++)
        {
            int iPlayerIx = m_vct_PlayerCircle[i].player;
            ASSERT(iPlayerIx >= 0 && iPlayerIx < m_lNumPlayers);

            if( m_vctPlayers[iPlayerIx].m_vcHand[j].m_eSeed == UNDEF)
            {
                            // assign it to empty place on hand
                m_vctPlayers[iPlayerIx].m_vcHand[j] = tmpCard;
                break;
            }
        }
                            // assertion because PescaNewCard should be done only if a player has a UNDEF card
        ASSERT(j < NUM_CARDS_HAND);
    }
    Utility::TraceContainer(m_vctPlayers, "Player status after new hand");
    
    if (m_lNextCard >= NUM_CARDS  )
    {
                            // no more cards to get
       bRes = false; 
    }

    return bRes;
}

////////////////////////////////////////
//       GetCardInTavola
/*! Return an index of the card on table
*/
bool  cBriscolaCore::GetCardInTavola(long *plCardIndex)
{
    if (plCardIndex == NULL)
        return false;

    *plCardIndex = m_crdOnTable.m_lIndex; 

    return true;
}


////////////////////////////////////////
//       GetPlayerStatistic
/*! Return the statistic on the player
// \param int iPlayerIx : player index
// \param PLAYER_STATISTIC &statPlayer : returne statistic reference 
*/
bool  cBriscolaCore::GetPlayerStatistic(int iPlayerIx, PLAYER_STATISTIC &statPlayer)
{
    statPlayer = m_vctPlayers[iPlayerIx].m_Statistic;
    
    return true;
}


////////////////////////////////////////
//       GetPlayerCardsTaken
/*! 
// \param int iPlayerIx : 
// \param VCT_LONG &vct_Cards : 
*/
BOOL  cBriscolaCore::GetPlayerCardsTaken(int iPlayerIx, VCT_LONG &vct_Cards)
{
    vct_Cards = m_vctPlayers[iPlayerIx].m_vctCardsTaken;
    
    return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// private functions


////////////////////////////////////////
//       GetNextCard
/*! Return the next card on card pull on table
// \param bool* pbEnd : return boolean result if card are present 
*/
long cBriscolaCore::GetNextCard(bool* pbEnd)
{
   long lResult = NOT_VALID_INDEX;
   if (m_lNextCard >= NUM_CARDS)
   {
      *pbEnd = false;
      return lResult; 
   }
   *pbEnd = true;

   lResult = m_vctCards[m_lNextCard];
   m_lNextCard ++;

   return lResult;
}

////////////////////////////////////////
//       ThrowTableCard
/*! Make the "briscola" and return the card index that lies on table (briscola)
*/
long cBriscolaCore::ThrowTableCard()
{
    long lResult = NOT_VALID_INDEX;
    if (m_lNextCard >= NUM_CARDS)
    {
        return lResult; 
    }

    lResult = m_vctCards[m_lNextCard];

                           // swap the next card with the last
    long lLast = m_vctCards[NUM_CARDS - 1]; 
    m_vctCards[NUM_CARDS - 1] = m_vctCards[m_lNextCard];
    m_vctCards[m_lNextCard] = lLast;

    return lResult; 
}

////////////////////////////////////////
//       WhoWinTheHand
/*! Decide who win the hand
*/
bool cBriscolaCore::WhoWinTheHand()
{
    VCT_LONG vct_Hand(m_lNumPlayers);

                            // set the hightest cards to the first played
    CardSpec HightCard = m_vctPlayedCards[0].second;
    int iMaxIndex = 0;
                            // vector of played cards indexs
    vct_Hand[0] = HightCard.m_lIndex; 
    
    for (unsigned int i = 1; i < m_vctPlayedCards.size(); i++)
    {
        CardSpec tmpCard = m_vctPlayedCards[i].second;
        vct_Hand[i] = tmpCard.m_lIndex;

        if ( !FirstCardIsBigger(HightCard, tmpCard))
        {
            HightCard = tmpCard;
            iMaxIndex = i;
        }
    }

    long lIndexPlayer = m_vctPlayedCards[iMaxIndex].first;
    ASSERT(lIndexPlayer >= 0 && lIndexPlayer < m_lNumPlayers);

                            // now we have a winner, update player score and statistic
    m_vctPlayers[lIndexPlayer].CatchTheHand(vct_Hand, m_crdOnTable);

    m_lPlayFirst = lIndexPlayer;

    return true;
}

////////////////////////////////////////
//       FirstCardIsBigger
/*! Return true if the the card c1 (first argument) is bigger (in briscola manner) as c2
//  FirstCardIsBigger assume that c1 was played first    
// \param  const CardSpec &c1 : first card played
// \param const CardSpec &c2 : second card played
*/
bool cBriscolaCore::FirstCardIsBigger( const CardSpec &c1, const CardSpec &c2)
{
    eSEED eBriscola = m_crdOnTable.m_eSeed; 
    ASSERT(c1.m_lIndex != c2.m_lIndex);
    ASSERT(c1.m_lIndex >= 0 && c1.m_lIndex < NUM_CARDS);
    ASSERT(c2.m_lIndex >= 0 && c2.m_lIndex < NUM_CARDS);

    if (c2.m_eSeed == eBriscola && c1.m_eSeed != eBriscola)
    {
                            // c2 is briscola and c1 not
        return false;
    }
    else if(c1.m_eSeed == eBriscola && c2.m_eSeed != eBriscola)
    {
                            // c1 is briscola and c2 not
        return true;
    }
    else
    {
                            // cards are not briscole
        if (c2.m_eSeed == c1.m_eSeed)
        {
                            // cards have the same seed
            int p1 = g_PointsTable[c1.m_lIndex];
            int p2 = g_PointsTable[c2.m_lIndex];

            if ( p1 > p2)
            {
                return true;
            }
            else if ( p1 < p2)
            {
                return false;
            }
            else
            {
                ASSERT(p1  == 0 && p2 == 0);
                               // cards are lisci, hightest index win
                if (c1.m_lIndex > c2.m_lIndex)
                {
                    return true;
                }
                else if(c1.m_lIndex < c2.m_lIndex)
                {
                    return false;
                }
                else
                {
                                // error condition
                    ASSERT(0);
                }
            }
        }
        else
        {
                            // cards have a different seed: first played win
            return true;
        }
    }
    ASSERT(0);
    return false;
}


////////////////////////////////////////
//       GetIndexNextCard
/*! Return the next card on top of the deck. No increment next card.
// \param bool* pbEnd : returned boolean result if card are present 
*/
long cBriscolaCore::GetIndexNextCard(bool* pbEnd)
{
   long lResult = NOT_VALID_INDEX;
   if (m_lNextCard >= NUM_CARDS)
   {
      *pbEnd = false;
      return lResult; 
   }
   *pbEnd = true;

   lResult = m_vctCards[m_lNextCard];
   
   return lResult;
}





