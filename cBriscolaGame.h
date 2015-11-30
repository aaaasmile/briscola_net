// cBriscolaGame.h

#ifndef _C_BRISCOLA_H_
#define _C_BRISCOLA_H_

#include "cUserMatrix.h"
#include "fuzzy.h"

#include <algorithm>
#include <vector>
#include <iostream>

typedef std::vector<long> VCT_LONG;
typedef VCT_LONG::iterator IT_VCTLONG;

//! enum for card server jpg status
enum
{
    ROT90 = 2,
    EMPTY = 5,
    INVISIBLE = 6,
    DRAWNORMAL = 4,
    MAZZO = 7
};

//! useful constants
enum
{
    //! index of me
    PLAYER_ME = 0,
    //! index of opponent
    PLAYER_OPPONENT = 1,
    //! number of cards + deck
    NUM_CARDS = 41,
    NUM_CARDS_HAND = 3,
    SCORE_GOAL = 60,
    NOT_VALID_INDEX = -1,
    TOTAL_POINTS = 120,
    NUM_SEEDS = 5,
    BUFF_NAME = 64,
    //!card on deck
    NUM_DECK_CARD = 33,
    //! deck index
    DECK_INDEX = 0,
    //! deck red
    DECK_RED_INDEX = 41,
    //! segni on match
    SEGNI_ON_MATCH = 4
};

//! type of cards
enum eSEED
{
    BASTONI = 0,
    DENARI = 1,
    SPADE = 2,
    COPPE = 3,
    UNDEF = 4
};

//! type of opponent
enum eOpponentType
{
    CPU_TYPE = 0,
    REMOTE_NET_TYPE = 1
};


//! briscola engine status
enum eBriscolaStatus
{
    //! new game
    NEW_GAME = 0,
    //! player 1 have to play
    WAITINGPLAYER_TOPLAY = 1,
    //! cpu have to play
    WAITING_CPU_TOPLAY = 2,
    //! a player have being played
    PLAYER_PLAYED = 3,
    //! game is terminated
    GAME_TERMINATED = 4,
    //! hand is terminated
    HAND_TERMINATED = 5,
    //! not ready
    NOT_READY_TO_PLAY = 6,
    //! generi error state
    FAULT = 100,
    //! wait for a new play
    GAME_WAIT_FOR_NEWGAME = 7,
    //! player 2 have to play
    WAITINGPLAYER_2_TOPLAY = 8,
    //! player 3 have to play
    WAITINGPLAYER_3_TOPLAY = 9,
    //! player 4 have to play
    WAITINGPLAYER_4_TOPLAY = 10,
    //! player 5 have to play
    WAITINGPLAYER_5_TOPLAY = 11,
    //! new game in network
    NEW_NET_GAME = 12,
    //! new segno
    NEW_SEGNO = 13,
    //! segno is terminated
    SEGNO_TERMINATED = 14,
    //! player is set, now wait for mazzo
    WAIT_FOR_MAZZO = 15,
    //! a net segno game have to begin
    NEW_NET_SEGNO = 16

};

//! game level
enum eGameLevel
{
    //! level dummy
    DUMMY = 0,
    //! level beginner
    BEGINNER = 1,
    //! level advanced
    ADVANCED = 2,
    //! level nightmare
    NIGHTMARE = 3
};

//! type of game
enum eGameType
{
    //! standard two player briscola
    BRISC_NORMINDUE,
    //! two player briscola undecked
    BIRSC_SCOPERTA
};

//! nature of the player
enum eTypeOfPLayer
{
    //! human
    PT_HUMAN,
    //! machine
    PT_MACHINE,
    //!remote player
    PT_REMOTE
};

//! structure to define the status of a player
typedef struct tag_PLAYER_CARD_ST
{
    //! player index
    long               player;
    //! briscola status
    eBriscolaStatus    status;
}PLAYER_CARD_ST;

//! structure for player statistic
typedef struct tag_PLAYER_STATISTIC
{
    //! actual score
    long    lScore;
    //! actual number of hand old
    long    lNumHand;
    //! actual number of briscole taken
    long    lNumBrisc;
    //! actual number of carac taken
    long    lNumCarac;
    //! number of strozzi remained
    long    bynStroz[NUM_SEEDS];
    //! number of Re remained
    long    bynRe[NUM_SEEDS];
    //! number of horse remained
    long    bynHorse[NUM_SEEDS];
    //! number of Fanti remained
    long    bynFanti[NUM_SEEDS];
    //! number of briscole remained
    long    lRemNumBrisc;
    //! number of points remained
    long    lRemNumPoints;
    //! last played seed first
    eSEED   eLastPlayed;
    //! number of briscole played
    long    bynBriscHad;
    //! points played
    long    bynPointsHad;
    //! points of briscole played
    long    bynBriscPointsHad;
    //! number of briscole on the first hand
    long    bynBriscFirstHad;
    //! number of carac played
    long    lCaracHad;
    //! number of briscole in hand
    long    lInHand_nBris;
    //! number of carac in hand
    long    lInHand_nCarac;
    //! number of lisci in hand
    long    lInHand_nLisc;
    //! number of segni wons
    long    lSegniWons;

    friend std::ostream &operator << (std::ostream &stream, const struct tag_PLAYER_STATISTIC &o);

}PLAYER_STATISTIC;

inline std::ostream &operator << (std::ostream &stream, const PLAYER_STATISTIC &o)
{ 
    stream << "---------------- new stat ------------------" << std::endl;
    stream << " punti totali = " << o.lScore << std::endl;
    stream << " num mani vinte = " << o.lNumHand << std::endl;
    stream << " num briscole prese = " << o.lNumBrisc << std::endl;
    stream << " num carichi presi = " << o.lNumCarac << std::endl;
    stream << " num briscole avute = " << o.bynBriscHad << std::endl;
    stream << " punti in briscole avuti = " << o.bynBriscPointsHad << std::endl;
    stream << " punti avuti = " << o.bynPointsHad << std::endl;
    stream << " num carichi giocati = " << o.lCaracHad << std::endl ;
    stream << " briscole in prima mano = " << o.bynBriscFirstHad << std::endl ;
    stream << std::endl;
   
    return stream;
}


//! structure for match statistic
typedef struct tag_MATCH_STATISTIC
{
    //! total segni wons
    long   lTotSegniWons;
    //! total segni losed
    long   lTotSegniLose;
   friend std::ostream &operator << (std::ostream &stream, const struct tag_MATCH_STATISTIC &o);
}MATCH_STATISTIC;

inline std::ostream &operator << (std::ostream &stream, const tag_MATCH_STATISTIC &o)
{ 
    stream << "---------------- new stat ------------------" << std::endl;
    stream << " segni totali vinti = " << o.lTotSegniWons << std::endl;
    stream << " segni totali persi = " << o.lTotSegniLose << std::endl;
    stream << std::endl;
   
    return stream;
}



/////////////////////////////////////////////////////////////////////////////////////
//     ***************************  CARDSPEC CLASS ******************************
/////////////////////////////////////////////////////////////////////////////////////

//! class CardSpec
class  CardSpec
{
public:
   CardSpec(){};
   virtual ~CardSpec(){};

   //! set the index of the card
   void SetCardIndex(long ltmpIndex);
   //! say if the card a is strozable
   bool CanStrozza( CardSpec &a, long *plPoints);
   // a was played first, calculate score of the actual card if it played
   bool CalcPoints(CardSpec &a, long *plPoints, CardSpec &Bris);

   void operator = (const CardSpec &r) {m_lIndex = r.m_lIndex; m_eSeed = r.m_eSeed;} 
 
public:
   //! index of the card
   long  m_lIndex;
   //! seed of the card
   eSEED m_eSeed;
};

typedef std::vector<CardSpec> VCT_CARDSPEC;

/////////////////////////////////////////////////////////////////////////////////////
// *********************************     CPLAYER CLASS  ****************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cPlayer 
class cPlayer
{
public: 
    cPlayer();
    virtual ~cPlayer(){};

    //! provides the player score
    long    CalculateScore();
    //! update statistic of the player
    bool    CatchTheHand(VCT_LONG &vctHand, CardSpec &cdBriscola);
    //! reset information about the player
    bool    ResetThePlayer();
    //! is the hand empty?
    bool    IsHandEmpty();
    //! initialize the player statistic
    void    InitPlayerStat();

    friend std::ostream &operator << (std::ostream &stream, const cPlayer &o);

public:
    //! cards on player's hand 
    VCT_CARDSPEC     m_vcHand;
    //! points score
    long             m_lScore;
    //! vector of cards taken
    VCT_LONG         m_vctCardsTaken;
    //! statistic on catched cards
    PLAYER_STATISTIC m_Statistic;
    //! playername
    CHAR             m_pPlayerName[BUFF_NAME];
    //! kind of player
    eTypeOfPLayer    m_eKind;
};

typedef std::vector<cPlayer>  VCT_PLAYERS;

//operators
inline std::ostream &operator << (std::ostream &stream, const cPlayer &o)
{ 
    stream << "Player" << std::endl;
    for (unsigned long l = 0; l < o.m_vcHand.size(); l++)
    {
        stream << o.m_vcHand[l].m_lIndex << "\t" ;
    }
    stream << std::endl;
   
    return stream;
}


/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CBRISCOLACORE CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cBriscolaCore
class cBriscolaCore
{
private:
    typedef std::pair<long, CardSpec>         PAIR_PLAYER_CARD;
    typedef std::vector<PAIR_PLAYER_CARD>     VCT_PAIR_PLAYER_CARD;
    typedef std::vector<PLAYER_CARD_ST>       VCT_PAIR_PLAYER_STATUS;
    typedef bool (cBriscolaCore:: *PFN_CPUPLAYER)(int, long*, long*);

protected:
    cBriscolaCore(){};

public:
    
    cBriscolaCore(int iNumPlayers);
    virtual ~cBriscolaCore(){};

    //! init a new match (on best of 4 segni)
    void  InitNewMatch();
    //! generate a new segno
    bool  InitPlay(long lIndexPl, eGameType eType);
    //! start a new hand
    bool  BeginNewHand();
    //! provides the card on the table (index)
    bool  GetCardInTavola(long *plCardIndex);
    //! provides the card index of a player index in the hand index 
    bool  GetCardInHand(int iPlayerIx, int iHandIx, long* plIndex);
    //! inform briscola engine that a player played a card in hand
    bool  CardIsPlayed(int iPlayerIx, int iHandIx);
    //! provides a player score
    bool  GetPlayerScore(int iPlayerIx, long *plScore);
    //! requery that the engine play for a player 
    bool  PlayACardDad(int iPlayerIx, long* plPlayedCard, long* lPosHand);
    //! provides briscola engine status
    bool  GetStatus(eBriscolaStatus* pSt);
    //! provides information about whon won the game
    bool  WhoWinTheGame(long* plPlayerIx, bool* pbIsDrawn);
    //! provides the index of the player that have to play
    bool  GetPlayerInPlaing(long * plPlayerIx);
    //! set briscola engine skill  
    bool  SetLevel(eGameLevel eNewLevel);
    //! provides a statistic of a player
    bool  GetPlayerStatistic(int iPlayerIx, PLAYER_STATISTIC &statPlayer);
    //! provides the index of the next card
    long  GetIndexNextCard(bool* pbEnd);
    //! provides the segni score
    bool  GetSegniScore(int iPlayerIx, long *plScore);
    //! set the type of a player
    bool  SetPlayerRemote( int iPlayerIx, eTypeOfPLayer eType);
    //! set the network game type
    void  SetNetGameType(eOpponentType eVal){m_eOppType = eVal;}
    //! provides the mazzo after shuffle
    VCT_LONG  GetStartMazzo(){return m_vctStartCards;}
    //! provides the player index that start the game
    long      GetStartPlayerIndex(){return m_lStartPlayer;}
    //! set the first player
    bool      SetFirstPlayer(long lIndexPl);
    //! init a game with a mazzo already shuffled
    bool      InitPlayWithMazzo(VCT_LONG& vct_Mazzo, eGameType eType);
    //! player abort the segno
    BOOL      PlayerAbortTheSegno(long lAbortPlayerIndey, BOOL bMazzo);
    //! player cards taken
    BOOL      GetPlayerCardsTaken(int iPlayerIx, VCT_LONG &vct_Cards);

    

private:
    long  GetNextCard(bool* pbEnd);
    long  ThrowTableCard();
    bool  WhoWinTheHand();
    bool  FirstCardIsBigger( const CardSpec &c1, const CardSpec &c2);
    bool  MakePlayerCircle();
    eBriscolaStatus StatusByIndexPlayer(int iPlayerIndex);
    bool  CPUPlayAlwaysTheFirst(int iPlayerIx, long* plPlayedCard, long* plPosHand);
    bool  CPUPlayBegginner(int iPlayerIx, long* plPlayedCard, long* plPosHand);
    bool  CPUPlayAdvanced(int iPlayerIx, long* plPlayedCard, long* plPosHand);
    bool  CanIStroz(CardSpec &crdPlayed, int iPlayerIx, long* plPosHand, VCT_LONG &vctlPoints);
    bool  CalcHandPoints(CardSpec &crdPlayed, int iPlayerIx, VCT_LONG &vctlPoints);
    bool  CalcAdvFirstPoints(int iPlayerIx, VCT_LONG &vPoints);
    bool  CalcAdvSecondPoints(CardSpec &crdPlayed, int iPlayerIx, VCT_LONG &vctlPoints);
    //! Update statistic after hand is terminated
    void  UpdateStatistic();
    //! Update statistic with cards in hand
    void  UpdateStatWithHand(int iPlayerIx);

private:
    //! vector of cards in the play (mazzo)
    VCT_LONG      m_vctCards;
    //! vector of cards at the start of the game (after shuffle)
    VCT_LONG      m_vctStartCards;
    //! index to the next card in the mazzo
    long          m_lNextCard;
    //! vector of players
    VCT_PLAYERS   m_vctPlayers;
    //! number of players
    long          m_lNumPlayers;
    //! card that make the briscola
    CardSpec      m_crdOnTable;
    //! player index that must play now
    long          m_lPlHaveToPlay;
    //! player index who play first in the current hand
    long          m_lPlayFirst;
    //! player index that has started the game
    long          m_lStartPlayer;
    //! vector of player indexs that must play and associated game status
    VCT_PAIR_PLAYER_STATUS    m_vct_PlayerCircle;
    //! vector of played cards in one hand
    VCT_PAIR_PLAYER_CARD      m_vctPlayedCards;
    //! game status
    eBriscolaStatus           m_eStatus;
    //! pointer to function used when CPU play
    PFN_CPUPLAYER             m_pFunCPUplayer ;
    //! level of the game
    eGameLevel                m_eGameLevel;
    //! type of game (scoperta or normal)
    eGameType                 m_eGameType;
    //! match statistic
    MATCH_STATISTIC           m_Match_Stat;
    //! opponent type
    eOpponentType             m_eOppType;
};

#endif