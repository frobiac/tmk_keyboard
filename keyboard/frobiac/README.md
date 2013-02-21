frobiac keyboard firmware
======================
DIY compact keyboard(s) designed and run frobiac using matrix arrangement of the AdNW ergonomic layout.
BlueCube is a split design with two 4x6 matrices, HyperNano a one-piece board with 4 rows with 5 keys and an additional 2 keys per thumb in the center. Both designs feature an integrated IBM PS/2 trackpoint that is not yet supported with this firmware.

My own current custom firmware can be found [here](http://github.com/frobiac/adnw)

## Threads on Deskthority.org
- [Prototyping](http://deskthority.net/workshop-f7/my-diy-keyboard-collection-or-how-i-became-a-kb-geek-t2534.html)


## Build
Move to this directory then just run `make` like:

   $ make -f Makefile.lufa  \[hypernano|bluecube]


## Boot Magic
TBD


## Keymap

Currently using a slightly adapted AdNW layout with programming and navigation layers inspired by neo-layout.org
Outer pinky columns are only available on BlueCube, and not displayed below.

See [keymap.c](keymap.c) for detail.

Note that the keymap is configured to be used on a host with QWERTZ driver. Therefore nearly all special characters in the code need to be mapped by means of FNxx actions since additional modifiers are often necessary.
### Layers
All layers utilize the same thumb-row for frequent keys and modifiers. This in not depicted below to keep the layers clean.
#### Layer 1: (lowercase char)
    k u q . j    v g c l f
    h i e a o    d t r n s
    x y - , /    b p w m z

#### Layer 2: (uppercase)
    K U Q : J    V G C L F
    H I E A O    D T R N S
    X Y _ ; /    B P W M Z

#### Layer 3: (symbol)
    @ € [ ] #    ! < > = &    See special note on QWERTZ remapping below!
    \   { } *    ? ( ) +
      $ | ~ `    ^ % " '

#### Layer 4: (navigation & numbers)
    ⇞ ⇤ ↑ ⇥ ⇟    ß 7 8 9 ä     ⇤,⇥ : backspace & delete
    ⇤ ← ↓ → ⇥    . 4 5 6 ö
    e ⇥ i ⏎      0 1 2 3 ü     e,i : esc & insert


#### Thumb-row
A common thumb-row setup is used in all layers: On the right hand side, modifiers to switch between all layers are located conveniently in the center, wheras the left thumb operates any additional modifiers, mainly for shortcuts in applications.
Note that most thumb-keys have two usage modes: When tapped on their own, frequent keys such as space, tab, backspace and return can be emitted. If used in conjunction with other keys, they act as layer (0-4) or control modifiers (S,A,C,G for shift, alt, ctrl, gui).
In mouse mode (when using the integrated trackpoint) they also act as mouse buttons.

##### Modifier mode

              0  4
    . S A C ␣ G  3 1 2 A . .

##### Keycode mode
              .  .
    . . . ⇥ ␣ .  e ⌫ ⏎ . . .   e = esc


### QWERTZ remapping
All characters that are different to qwerty are created with actions that set the correct modifiers, e.g.

    // @ is RALT+q and mapped to FN23
    ACTION_RMOD_KEY(KC_RALT, KC_Q), // AltGr+q = @ 


The number row is different:

    Normal: ^ 1 2 3 4 5 6 7 8 9 0 ß ´ 
    Shift : ° ! " § $ % & / ( ) = ? `
    AltGr : ¬ ¹ ² ³ ¼ ½ ¬ { [ ] } \ ¸

On QWERTZ, the other hid codes are translated according to the following table (normal,shifted and with right alt):

    Y    Z    E    Q    SLSH BSLS MINS EQL  GRV  NUBS QUOT SCLN LBRC RBRC 
    z    y    e    q    -    #    ß    ´    ^    <    ä    ö    ü    +    
    Z    Y    E    Q    _    '    ?    `    °    >    Ä    Ö    Ü    *    
              €    @              \              |         ˝    "    ~

Some characters can be used from the numpad:

    PSLS PAST PMNS PPLS PDOT PEQL
    /    *    -    +    .    = 



