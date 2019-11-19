#!/bin/bash

# Write pretty status message
message_running() {
    example_name=$1
    shift
    executable=$1
    shift
    options=$@

    echo "***************************************************************"
    echo "* Running Example $example_name:"
    echo "*  $LIBMESH_RUN ./$executable $options $LIBMESH_OPTIONS"
    echo "***************************************************************"
    echo " "
}

# Write pretty status message
message_done_running() {

    example_name=$1
    shift
    executable=$1
    shift
    options=$@

    echo " "
    echo "***************************************************************"
    echo "* Done Running Example $example_name:"
    echo "*  $LIBMESH_RUN ./$executable $options $LIBMESH_OPTIONS"
    echo "***************************************************************"
}

run_example() {

    example_name=$1
    shift
    options=$@

    message_running $example_name $executable $options

    gcc ./$executable $options $LIBMESH_OPTIONS
        RETVAL=$?
        # If we don't return 'success' or 'skip', quit
        if [ $RETVAL -ne 0 -a $RETVAL -ne 77 ]; then
          exit $RETVAL
        fi
    
    message_done_running $example_name $executable $options
    
}

run_example_no_extra_options() {
  LIBMESH_OPTIONS='' run_example $@
}
