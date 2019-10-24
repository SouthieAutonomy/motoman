# DynamicJointsGroup
#group: # length of this array must match num_groups
#    id:   control-group ID for use on-controller
#    num_joints: # of joints in this motion group
#    valid_fields: #bit field for following items

#    !! Jay, More on invalid fields: (from http://roswiki.autolabor.com.cn/attachments/motoman_driver/MotoRos_EDS.pdf)
#        Bit-mask indicating which “optional” fields are filled with data.
#        1 = time, 2 = position, 4 = velocity, 8 = acceleration
#        MotoROS expects all values, so this value should be set to 7.

#    # length of the following items must match num_joints, order set by controller.
#    # Invalid fields (see bit field above) are not included, resulting in a shorter message.
#    positions[]
#    velocities[]
#    accelerations[]
#    effort[]
#    time_from_start


int16 group_number
int16 num_joints
int16 valid_fields
float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
duration time_from_start
