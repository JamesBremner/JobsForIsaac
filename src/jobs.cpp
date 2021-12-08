
#include "entitydb.h"

class cApp
{
public:
    cApp();
    void run()
    {
        myForm.run();
    }

private:
    wex::gui &myForm;
    raven::edb::cEntityForm myJobForm;
    raven::edb::cEntityForm myPartForm;

    void hide();

    void ConstructMenus();
};

cApp::cApp()
    : myForm(wex::maker::make()),
      myJobForm(raven::edb::cEntityForm(
          myForm, "job",
          {"DESCRIPTION",
           "START",
           "ASSIGN"})),
      myPartForm(raven::edb::cEntityForm(
          myForm, "part",
          {
           "START",
           "END",
           "MATERIAL"}))
{
    raven::edb::open(
        "jobs.dat");

    raven::edb::createCategory(
        "job",
        {"DESCRIPTION", "START", "ASSIGN"});

    raven::edb::createCategory(
        "part",
        {"START", "END", "MATERIAL"});

    raven::edb::createLink(
        "partof",
        "part",
        "job");
     myPartForm.link("JOB","partof");

    // raven::edb::createLink(
    //     "spouse",
    //     "parent",
    //     "parent");
    // myParentForm.link("Spouse", "spouse" );

    myForm.move({50, 50, 600, 800});
    myForm.text("Jobs For Isaac");

    ConstructMenus();

    myForm.show();
    hide();
}
void cApp::hide()
{
    myJobForm.show("-1", false);
    myPartForm.show("-1", false);
}

void cApp::ConstructMenus()
{
    wex::menubar mbar(myForm);
    wex::menu m(myForm);
    m.append("JOBS",
             [&](const std::string &title)
             {
                 raven::edb::cEntityList L(
                     "JOBS",
                     "job");
                 hide();
                 myJobForm.show(L.mySelected);
             });
    m.append("JOB PARTS",
             [&](const std::string &title)
             {
                 raven::edb::cEntityList L(
                     "JOB PARTS",
                     "part");
                 hide();
                 myPartForm.show(L.mySelected);
             });
    m.append("EMPLOYEES",
             [&](const std::string &title) {
             });
    m.append("MATERIALS",
             [&](const std::string &title) {
             });
    m.append("VEHICLES",
             [&](const std::string &title) {
             });
    mbar.append("Tables", m);
}

cApp *theApp;

main()
{
    theApp = new cApp();
    theApp->run();
}