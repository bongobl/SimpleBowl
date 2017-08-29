#ifndef CONTRACT
#define CONTRACT


namespace sb{

    class Game;
    class Round;

    class Contract{

        Round* round;
        int times;

    public:
        Contract(Round* r, int t);
        friend class Game;
    };

}

#endif // CONTRACT
