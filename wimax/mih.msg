// ********************************************************************************
// *** Media Independent Handover: messages used to notify other layers ***********
// ********************************************************************************

// used to report that L2 entry started
message MihEvent_EntryStart
{

};

// used to report that L2 entry finished
message MihEvent_EntryEnd
{

};

// used to report that L2 handover started
message MihEvent_HandoverStart
{

};

// used to report by WMaxPhySS to WMaxCtrlSS that HO-IND was actually transmitted
message MihEvent_HandoverEnd
{

};

// used to report that L2 reentry started
message MihEvent_ReentryStart
{


};

// used to report that L2 reentry finished
message MihEvent_ReentryEnd
{

};
