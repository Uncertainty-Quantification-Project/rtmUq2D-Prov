#include "dfanalyzer.h"

void main(void) {
    Dataflow dataflow = Dataflow("rtm");
    cout << dataflow.get_tag() << endl;

    //runrtm inputsets
    vector<string> attribute_names = {"velocityFile", "waveletFile" , "nx", "nz", "simulation"};
    vector<attribute_type> attribute_types = {RDFILE , RDFILE , NUMERIC, NUMERIC,NUMERIC};
    Set& irunrtm = dataflow.add_set("irunrtm", attribute_names, attribute_types);

    attribute_names = {"seismogram_path", "simulation", "shot"};
    attribute_types = {RDFILE , NUMERIC, NUMERIC};
    Set& iseismogram = dataflow.add_set("iseismogram", attribute_names, attribute_types);

    vector<Set> inputSets = {irunrtm, iseismogram};

    //runrtm outputset
    attribute_names = {"cross_correlation","self_cross_correlation", "shot", "shotLocation"};
    attribute_types = {RDFILE, RDFILE , NUMERIC, NUMERIC};
    Set& orunrtm = dataflow.add_set("orunrtm", attribute_names, attribute_types);
    
    //transformation runRTM
    Transformation& runrtm= dataflow.add_transformation("runrtm", inputSets, orunrtm);

    //set ostacking
    attribute_names = {"stacked_section", "laplacian_stacked_section", "total_rtm_time"};
    attribute_types = {RDFILE, RDFILE,NUMERIC};
    Set& oStacking = dataflow.add_set("ostacking", attribute_names, attribute_types);    

    //transformation stacking
    Transformation& stacking = dataflow.add_transformation("stacking", orunrtm, oStacking);

     //set ostacking
    attribute_names = {"total_simulations", "total_time"};
    attribute_types = {NUMERIC,NUMERIC};
    Set& oExecution = dataflow.add_set("oexecution", attribute_names, attribute_types);    

    //transformation stacking
    Transformation& execution = dataflow.add_transformation("execution", oStacking, oExecution);
    
    dataflow.save();
}