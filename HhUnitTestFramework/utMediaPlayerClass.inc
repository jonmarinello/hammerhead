class UtMediaPlayer : public HH_UnitTest
{
public:
    UtMediaPlayer( bool& variableDataGeneration, bool interactive )
        : HH_UnitTest( variableDataGeneration, interactive )
    {
    }

    ~UtMediaPlayer()
    {
    }

protected:
    void TestCommands();
    void HelpForTestCommands();

private:
    std::auto_ptr< MP_MediaPlayer >   m_pMediaPlayer;
};
