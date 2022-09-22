
// parsered from data4student.txt

// Alice's public key
const char *e = "65537";
const char *N = "20955719787022750516413100491376771572395669367702302766047037068317739117834815896320273069621410724686451673516116146223996675358532982455366637459484069804038574030493139707679137562409152505863034331903654335925501024675071494498684002075692198002066758834324162665791713407388966481825051924490098656040703195512575205133855417526680573665122280291023088604299585594187383205142622299334866758304843638068617926635940437613394642831015652496647051766102742797978950405247240662292495506034093966684312351092184174431122655986295602361602404305330128306117887844807960210617670543847849776423583667209212600353553";

// msg
const char *msg1 = "2";
const char *msg2 = "3076";
const char *msg3 = "1840018905516359258";
const char *msg4 = "115169718963512512097";
const char *msg5 = "230339437927025024194";
const char *msg6 = "1621528925132306315405134199";
const char *msg7 = "3243057850264612630810268398";
const char *msg8 = "202988165000714305156261265107";
const char *msg9 = "700301767868211248235098884477038220114257311";
const char *msg0 = "470370683177391178348158963202730696214107246864516735";

// sig
const char *sig1 = "8094291632055599563247859443053140337665563821893717229254173990810006234042629054510291877249487522567533047352881291315591579624814500138551354129074909934140130926411361913657309037822096181123221883904676066011215903115610005036709293152373219484871643127635625666988560250425376303737864634438376979549536888683584536961900655514010656136121629294321201919898669197849911895814358045720240522224252028726416335477977797653834607548960393275486404100149353313056418219223915361867575641523186529191336647204154200198842838412157958232224288938938160394131024837035292086746012807693399905957981798091854738809604";
const char *sig2 = "13750564747951671204111620546935754717472400438268699132351209906487771396961827813219293066011639215583188341880321446915812296123410413151119767575785630025475289806093065673233270935832007574552234186933032185010712681951010625633780865010785376145034341227531896689128236564597980306694355063132899781783839697481992279048299476495353951889405421636134253358204990247288318533345045566854938827412124283301329150250618519742853197161665815775921492895353069482289491559188568002134602860349816049414510806073554558844499691777352332949219306123015995684870917980253494788173362919490936355323834882513724972473727";
const char *sig3 = "12908685646529788085423968604439862429920919775452980296289078667460766098530378956302848858019175431269162169075211073737441801750356604798907102652399849265623323960133406244233930369587214384216616053094089711495550171201427351859276368842225561962544084011010810878285171628613902855429194305556239075452561501613808379419578428107771706670213681995760143741831827381548847128433891342114916428088021210550744628868990972497098665273328803794493497622797543989458114394405044941838595887121186634136804131854684322838540992590481011331967385381899151842052907240428940444459617460761711108444299108355832626048645";
const char *sig4 = "18526998781937159129491823259376854111513151264610266124893825623928444484643625577931239609336171762540989039015348628156834789913611876016535746555503271028007604308179068148057539922780130575243016062859964520545531591109309424557351937515051509196897026435001497110914515672107924347718139254823766147636065844011543163897891053824861093676125009103968295952279719232866078748730490946083833326157690557282762834051817881269354383725924717196472434935936670432001156874164196855743096464963657066959090903069269656951041945569585326919965921843138671431369142883386666557264768844139031918396065542104866517068013";
const char *sig5 = "18041190429199565969245308782746477561024310391338252094811126342873569434628909086192300301920061734263599589853517545207736337538246534122148871535928566860223495493935458294187322054936019873593827453779554972016165259362945813828470078155461131064949328739204418703707918967209110156680520682741689906239912442647443750186419871605497077904836319704976271317428456784109178627115076264723049137712336121023260193085743665795500606354312506658289422276083290768364600159716394277950330065531419670888935601572055257247107508946509429775481330301290692988228144459879720023925900555489798781231708515302551071221104";
const char *sig6 = "8662533687603540921053864175619856381001634777691981334738889704576658708291937130777940928887339033498906806046210178332816846411476765399801838581805710972503278093553913025703936313220103494955508946457260932707520418626079236700930669630719614066662586800436668550665963926083003421094164122185996706390947657863256947591693569214251489796712941661780670025968601022915237693691667950798638154670494445068778861630517942003503885100151366785693760010875520203762398314008089145137954832709613225286856154943432563671644016686382535895280752997008539134081239824946577136153651466516515234767260994568198281777867";
const char *sig7 = "3979858860299204508871438682497173749555979734887156139265234566061790119762828686170298434898827376429638168348595099289774203319909940276089869359527908498076527974632292082637148773745466208477967495361594730361639007040830155298369289919942808496374337209159581017235754306571762665646284813221299573178728393598108199602177571010068674906185827518236779398383765973709521294808077216255926966526273687725712794183637871620779266709246053781182593677066448440469780210104430318594399634047246446823186700515336183524619144160424563302327259808716407808571318098566449109510047593211391821972280774710032070837295";
const char *sig8 = "10495268195597817294863043246412507797240570730647727242594296652366173557855207597891996323113814935847553088982691420868744127483016749990448112459919745739483631827068387395185698130441481038025169700151842249774605920612868226641511343808017604843214326449742999181373643961450575737258121293488439140594330245147810766336762093207726555689341923508514826469115190942034405908263965762825921588106275899821085262399244525864857394875244591804169692548854938968275546878348582748865504489116956211358594823426511284657227017591884657073920055228570162754928036484454726759792627407291427409242640277545991722100614";
const char *sig9 = "5397821233979199423480146387906449475318353765901898096709521045401620955203153861224846946865333584142351044077071836726907316859916405698894333886618036368961383920394470793251477332011836893200477562183490066211552738225518553015759676809636936443360592076143244732723796388243910299508371641007914510732502544618986683212149793859180138797162558065491975479036235119655615537663194343946336114750166446136130119719021816120966465984353355874043147794447087090770616956091477227341163523142984349374098712912551316019615757235303186788248206909359514524122770973507904066749133883621144883849219510293518299341257";
const char *sig0 = "20485631682361989595040991900385053123566141679740186291682002926548694816193733394332507711424055620139309868204926194725427153839008782164264234748682104725298604764798793863479262790115806717885022377852911699119839286614128884058046259176144202208577256908709337993257801346876605434434939484356916624800989323536327653238482738408672797511358829124943921995790766076651434238496483818978182411548073307328012329805200723124902936109281173054226590274998187768722194211736851774732629486875689088730944550575343704552212711278451896243354067762551527705492795963996183522121442256595818457447073531426877905843973";

using str_t = const char *;

const str_t msg_lst[10]{
    msg1,
    msg2,
    msg3,
    msg4,
    msg5,
    msg6,
    msg7,
    msg8,
    msg9,
    msg0};

const str_t sig_lst[10]{
    sig1,
    sig2,
    sig3,
    sig4,
    sig5,
    sig6,
    sig7,
    sig8,
    sig9,
    sig0};