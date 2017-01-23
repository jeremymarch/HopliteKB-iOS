//
//  KeyboardViewController.swift
//  HCPolytonicGreekKB
//
//  Created by Jeremy March on 12/24/16.
//  Copyright © 2016 Jeremy March. All rights reserved.
//

import UIKit
/*
//http://norbertlindenberg.com/2014/12/developing-keyboards-for-ios/
extension UIInputView: UIInputViewAudioFeedback {
    
    public var enableInputClicksWhenVisible: Bool { get { return true } }
    
    func playInputClick​() {
        UIDevice.current.playInputClick()
    }
}
*/
class KeyboardViewController: UIInputViewController {

    var capsLockOn = false
    let bgColor = UIColor.init(red: 200/255.0, green: 200/255.0, blue: 200/255.0, alpha: 1.0)
    let keyTextColor = UIColor.black
    let useAnimation = false
    var deleteHoldTimer:Timer? = nil
    let stackView1   = UIStackView()
    let stackView2   = UIStackView()
    let stackView3   = UIStackView()
    let stackView4   = UIStackView()
    //var deleteButton:UIButton? = nil
    var globeButton:UIButton? = nil
    var capsLockButton:UIButton? = nil
    /*
    override func updateViewConstraints() {
        super.updateViewConstraints()
        // Add custom view sizing constraints here
    }
    */
    /*
    override func viewDidAppear(_ animated:Bool) {
        super.viewDidAppear(animated)
    
        for gesture:UIGestureRecognizer in (self.view.window?.gestureRecognizers!)!
        {
            gesture.delaysTouchesBegan = false
        }
    }
    */
    
    override func viewDidLoad() {
        super.viewDidLoad()
        NSLog("kb view did load")
        self.view.translatesAutoresizingMaskIntoConstraints = true //this is needed
        self.view.isUserInteractionEnabled = true
        self.view.backgroundColor = bgColor
        
        let buttonSpacing:CGFloat = 5.0
        let widthMultiple:CGFloat = 0.0976

        /*
         let upperBorder: CALayer = CALayer()
         upperBorder.backgroundColor = UIColor.green.cgColor
         upperBorder.frame = CGRect(x:0,y:0,width:self.view.frame.width,height:4)
         self.view.layer.addSublayer(upperBorder)
         */
        
        //is this needed?  it seems to be
        /*
        self.view.widthAnchor.constraint(equalToConstant: UIScreen.main.bounds.size.width).isActive = true
        self.view.heightAnchor.constraint(equalToConstant: 315).isActive = true
        let margins = view.layoutMarginsGuide
        self.view.leadingAnchor.constraint(equalTo: margins.leadingAnchor).isActive = true
        self.view.trailingAnchor.constraint(equalTo: margins.trailingAnchor).isActive = true
        
        self.view.topAnchor.constraint(equalTo: self.view.layoutMarginsGuide.topAnchor).isActive = true
        self.view.bottomAnchor.constraint(equalTo: self.view.layoutMarginsGuide.bottomAnchor).isActive = true
        */


        //Stack View

        stackView1.axis  = UILayoutConstraintAxis.horizontal
        stackView1.distribution  = UIStackViewDistribution.equalSpacing
        stackView1.alignment = UIStackViewAlignment.center
        stackView1.spacing   = buttonSpacing
        
        stackView2.axis  = UILayoutConstraintAxis.horizontal
        stackView2.distribution  = UIStackViewDistribution.equalSpacing
        stackView2.alignment = UIStackViewAlignment.center
        stackView2.spacing   = buttonSpacing
        
        stackView3.axis  = UILayoutConstraintAxis.horizontal
        stackView3.distribution  = UIStackViewDistribution.equalSpacing
        stackView3.alignment = UIStackViewAlignment.center
        stackView3.spacing   = buttonSpacing
        
        stackView4.axis  = UILayoutConstraintAxis.horizontal
        stackView4.distribution  = UIStackViewDistribution.equalSpacing
        stackView4.alignment = UIStackViewAlignment.center
        stackView4.spacing   = buttonSpacing
        
        let stackView5   = UIStackView()
        stackView5.axis  = UILayoutConstraintAxis.horizontal
        stackView5.distribution  = UIStackViewDistribution.equalSpacing
        stackView5.alignment = UIStackViewAlignment.center
        stackView5.spacing   = buttonSpacing
        
        let stackViewV  = UIStackView()
        stackViewV.axis  = UILayoutConstraintAxis.vertical
        stackViewV.distribution  = UIStackViewDistribution.equalSpacing
        stackViewV.alignment = UIStackViewAlignment.center
        stackViewV.spacing   = buttonSpacing
        
        stackView1.translatesAutoresizingMaskIntoConstraints = false;
        stackView2.translatesAutoresizingMaskIntoConstraints = false;
        stackView3.translatesAutoresizingMaskIntoConstraints = false;
        stackView4.translatesAutoresizingMaskIntoConstraints = false;
        stackView5.translatesAutoresizingMaskIntoConstraints = false;
        stackViewV.translatesAutoresizingMaskIntoConstraints = false;
        
        stackViewV.addArrangedSubview(stackView1)
        stackViewV.addArrangedSubview(stackView2)
        stackViewV.addArrangedSubview(stackView3)
        stackViewV.addArrangedSubview(stackView4)
        stackViewV.addArrangedSubview(stackView5)
        
        /*
        Also need:
            period
            comma
            raised dot, ano teleia
            question mark
        */
        let keys: [[String]] = [["῾", "᾿", "´", "`", "˜", "¯", "ͺ", ";","·"],
                                ["ε", "ρ", "τ", "υ", "θ", "ι", "ο", "π"],
                               ["α", "σ", "δ", "φ", "γ", "η", "ξ", "κ", "λ"],
                               ["ζ", "χ", "ψ", "ω", "β", "ν", "μ", "ς"],
                               ["CP", "KB", "space", ".", "enter", "BK"]]

        let fontSize:CGFloat = 24.0
        
        for row in keys
        {
            for key in row
            {
                var b:UIButton

                if row == keys[0]
                {
                    b = HCAccentButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    b.layer.cornerRadius = 4.0
                    //b.titleLabel?.textColor = UIColor.black
                    //b.setTitleColor(keyTextColor, for: [])
                    
                    //b.titleLabel!.transform = CGAffineTransform.init(scaleX: 2, y: 2)// .identity.scaledBy(x: 1.5, y: 1.5)
                    
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    if key == "´"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == "˜"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == "`"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == "¯"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(16, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == "῾"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(12, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == "᾿"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(12, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == "ͺ"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: 40)
                        b.titleEdgeInsets = UIEdgeInsetsMake(-24, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == ";"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                        
                    }
                    else if key == "·"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    }
                    else if key == "()"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    
                    stackView1.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                    //b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: 0.2).isActive = true
                    b.heightAnchor.constraint(equalToConstant: 42.0).isActive = true
                }
                else if row == keys[1]
                {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    b.layer.cornerRadius = 4.0
                    b.titleLabel?.textColor = UIColor.black
                    b.setTitleColor(keyTextColor, for: [])
                    b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    stackView2.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                }
                else if row == keys[2]
                {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    b.layer.cornerRadius = 4.0
                    b.titleLabel?.textColor = UIColor.black
                    b.setTitleColor(keyTextColor, for: [])
                    b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    stackView3.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                }
                else if row == keys[3]
                {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    b.layer.cornerRadius = 4.0
                    b.titleLabel?.textColor = UIColor.black
                    b.setTitleColor(keyTextColor, for: [])
                    b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    stackView4.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                }
                else if row == keys[4]
                {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    b.layer.cornerRadius = 4.0
                    b.titleLabel?.textColor = UIColor.black
                    b.setTitleColor(keyTextColor, for: [])
                    b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    if key == "CP"
                    {
                        b = HCCapsLockButton()
                        
                        //b.layer.borderWidth = 1.0
                        //b.layer.borderColor = UIColor.blue.cgColor
                        b.layer.cornerRadius = 4.0
                        b.titleLabel?.textColor = UIColor.black
                        b.setTitleColor(keyTextColor, for: [])
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.layer.backgroundColor = UIColor.brown.cgColor
                        b.setTitle("", for: [])
                        
                        b.addTarget(self, action: #selector(capsPressed(_:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                        
                        capsLockButton = b
                    }
                    else if key == "KB"
                    {
                        b = HCGlobeButton()
                        
                        //b.layer.borderWidth = 1.0
                        //b.layer.borderColor = UIColor.blue.cgColor
                        b.layer.cornerRadius = 4.0
                        b.titleLabel?.textColor = UIColor.black
                        b.setTitleColor(keyTextColor, for: [])
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.layer.backgroundColor = UIColor.brown.cgColor
                        b.setTitle("", for: [])
                        
                        //b.setTitle("", for: [])
                        b.addTarget(self, action: #selector(handleInputModeList(from:with:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                        
                        globeButton = b
                    }
                    else if key == "enter"
                    {
                        b.addTarget(self, action: #selector(returnPressed(_:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        
                        b.setTitleColor(UIColor.white, for: [])

                        b.layer.backgroundColor = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0).cgColor
                        
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: (widthMultiple * 2)).isActive = true
                    }
                    else if key == "space"
                    {
                        b.setTitleColor(UIColor.gray, for: [])
                        //b.layer.borderColor = UIColor.gray.cgColor
                        b.addTarget(self, action: #selector(spacePressed(_:)), for: .touchUpInside)
                        //b.addTarget(self, action: #selector(didDoubleTapSapce(_:)), for: .touchDownRepeat)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: (widthMultiple * 2.5)).isActive = true
                    }
                    else if key == "."
                    {
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                    }
                    else if key == "BK"
                    {
                        b = HCDeleteButton(devicea:2)
                        
                        //b.layer.borderWidth = 1.0
                        //b.layer.borderColor = UIColor.blue.cgColor
                        //b.layer.cornerRadius = 4.0
                        //b.titleLabel?.textColor = UIColor.black
                        //b.setTitleColor(keyTextColor, for: [])
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.layer.backgroundColor = UIColor.brown.cgColor
                        //b.setTitle(key, for: [])
                        
                        let lpgr = UILongPressGestureRecognizer(target: self, action: #selector(longDeletePressGesture))
                        lpgr.minimumPressDuration = 0.5
                        lpgr.delaysTouchesBegan = false //needed so it also listens for touchdown
                        lpgr.allowableMovement = 50.0
                        b.addGestureRecognizer(lpgr)
 
                        //need both long and normal
                        b.addTarget(self, action: #selector(backSpacePressed(_:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: (widthMultiple * 1.3)).isActive = true
                        
                        //deleteButton = b
                    }
                }
            }
        }
        
        self.view.addSubview(stackViewV)
        
        stackViewV.rightAnchor.constraint(equalTo: self.view.rightAnchor).isActive = true
        stackViewV.leftAnchor.constraint(equalTo: self.view.leftAnchor).isActive = true
        stackViewV.topAnchor.constraint(equalTo: self.view.topAnchor, constant:buttonSpacing).isActive = true
        stackViewV.bottomAnchor.constraint(equalTo: self.view.bottomAnchor, constant:-buttonSpacing).isActive = true
    }
    
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        super.viewWillTransition(to: size, with: coordinator)
        //updateViewConstraints()
        globeButton?.setNeedsDisplay() //to redraw globe icon
        capsLockButton?.setNeedsDisplay()
    }
 
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated
    }
    
    override func textWillChange(_ textInput: UITextInput?) {
        // The app is about to change the document's contents. Perform any preparation here.
    }
    
    override func textDidChange(_ textInput: UITextInput?) {
        // The app has just changed the document's contents, the document context has been updated.
        
        var textColor: UIColor
        let proxy = self.textDocumentProxy
        if proxy.keyboardAppearance == UIKeyboardAppearance.dark {
            textColor = UIColor.white
        } else {
            textColor = UIColor.black
        }
        //self.nextKeyboardButton.setTitleColor(textColor, for: [])
    }
    
    let COMBINING_GRAVE =            0x0300
    let COMBINING_ACUTE =            0x0301
    let COMBINING_CIRCUMFLEX =       0x0302
    let COMBINING_MACRON =           0x0304
    let COMBINING_DIAERESIS =        0x0308
    let COMBINING_SMOOTH_BREATHING = 0x0313
    let COMBINING_ROUGH_BREATHING =  0x0314
    let COMBINING_IOTA_SUBSCRIPT =   0x0345
    let EM_DASH =                    0x2014
    let LEFT_PARENTHESIS =           0x0028
    let RIGHT_PARENTHESIS =          0x0029
    let SPACE =                      0x0020
    let EN_DASH =                    0x2013
    let HYPHEN =                     0x2010
    let COMMA =                      0x002C
    
    func accentPressed(_ button: UIButton) {
        let whichAccent = button.titleLabel!.text
        var accent = -1
        if whichAccent == "´"
        {
            accent = 1
        }
        else if whichAccent == "˜"
        {
            accent = 2
        }
        else if whichAccent == "`"
        {
            accent = 3
        }
        else if whichAccent == "¯"
        {
            accent = 4
        }
        else if whichAccent == "῾"
        {
            accent = 5
        }
        else if whichAccent == "᾿"
        {
            accent = 6
        }
        else if whichAccent == "ͺ"
        {
            accent = 7
        }
        else if whichAccent == "()"
        {
            accent = 8
        }
        else
        {
            return;
        }
        
        
        let context = self.textDocumentProxy.documentContextBeforeInput
        let len = context?.characters.count
        if len == nil || len! < 1
        {
            return;
        }
        
        //accentSyllable(&context?.utf16, context.count, &context.count, 1, false);
        /*
         let bufferSize = 200
         var nameBuf = [Int8](repeating: 0, count: bufferSize) // Buffer for C string
         nameBuf[0] = Int8(context![context!.index(before: context!.endIndex)])
         accentSyllableUtf8(&nameBuf, 1, false)
         let name = String(cString: nameBuf)
         */
        
        let combiningChars = [COMBINING_GRAVE,COMBINING_ACUTE,COMBINING_CIRCUMFLEX,COMBINING_MACRON,COMBINING_DIAERESIS,COMBINING_SMOOTH_BREATHING,COMBINING_ROUGH_BREATHING,COMBINING_IOTA_SUBSCRIPT]
        
        let bufferSize16 = 5
        var buffer16 = [UInt16](repeating: 0, count: bufferSize16) // Buffer for C string
        
        var lenToSend = 1
        let maxCombiningChars = 5
        for a in (context!.unicodeScalars).reversed()
        {
            if lenToSend < maxCombiningChars && combiningChars.contains(Int(a.value))
            {
                lenToSend += 1
            }
            else
            {
                break
            }
        }
        
        let suf = context!.unicodeScalars.suffix(lenToSend)
        var j = 0
        for i in (1...lenToSend).reversed()
        {
            buffer16[j] = UInt16(suf[suf.index(suf.endIndex, offsetBy: -i)].value)
            j += 1
        }
        var len16:Int32 = Int32(lenToSend)
        
        accentSyllable16(&buffer16, 0, &len16, Int32(accent), true)
        
        let newLetter = String(utf16CodeUnits: buffer16, count: Int(len16))
        
        (textDocumentProxy as UIKeyInput).deleteBackward() //seems to include any combining chars
        (textDocumentProxy as UIKeyInput).insertText("\(newLetter)")
        
        if useAnimation
        {
            UIView.animate(withDuration: 0.2, animations: {
                button.transform = CGAffineTransform.identity.scaledBy(x: 2.0, y: 2.0)
            }, completion: {(_) -> Void in
                button.transform =
                    CGAffineTransform.identity.scaledBy(x: 1, y: 1)
            })
        }
    }
    
    func keyPressed(button: UIButton) {
        //NSLog("key pressed")
        let string = button.titleLabel!.text
        (textDocumentProxy as UIKeyInput).insertText("\(string!)")
        UIDevice.current.playInputClick()
        
        if useAnimation
        {
            UIView.animate(withDuration: 0.2, animations: {
                button.transform = CGAffineTransform.identity.scaledBy(x: 2.0, y: 2.0)
            }, completion: {(_) -> Void in
                button.transform =
                    CGAffineTransform.identity.scaledBy(x: 1, y: 1)
            })
        }
    }
    
    func backSpacePressed(_ button: UIButton) {
        (textDocumentProxy as UIKeyInput).deleteBackward()
    }
    
    func longDeletePressGesture(gestureReconizer: UILongPressGestureRecognizer) {
        
        if ( gestureReconizer.state == UIGestureRecognizerState.began )
        {
            self.deleteHoldTimer = Timer.scheduledTimer(timeInterval: 0.085, target: self, selector: #selector(backSpacePressed(_:)), userInfo: nil, repeats: true)
            
            let theRunLoop = RunLoop.current
            theRunLoop.add(self.deleteHoldTimer!, forMode: RunLoopMode.defaultRunLoopMode)
        }
        else if ( gestureReconizer.state == UIGestureRecognizerState.ended )
        {
            self.deleteHoldTimer!.invalidate();
            self.deleteHoldTimer = nil
            
            //need this or it stays in the down state
            let db:HCDeleteButton = gestureReconizer.view as! HCDeleteButton
            db.touchUpInside1(sender: db)
        }
        //NSLog(@"lg: %ld", (long)gesture.state);
    }
    
    func spacePressed(_ button: UIButton) {
        (textDocumentProxy as UIKeyInput).insertText(" ")
    }
    func didDoubleTapSapce(_ button: UIButton) {
        (textDocumentProxy as UIKeyInput).insertText(". ")
    }
    
    func returnPressed(_ button: UIButton) {
        (textDocumentProxy as UIKeyInput).insertText("\n")
    }
    
    func capsPressed(_ button: UIButton) {
        capsLockOn = !capsLockOn
        changeCaps(stackView2)
        changeCaps(stackView3)
        changeCaps(stackView4)
        //changeCaps(row4)
    }
    func changeCaps(_ containerView: UIView) {
        for view in containerView.subviews {
            if let button = view as? UIButton {
                let buttonTitle = button.titleLabel!.text
                
                //final sigma alternates with digamma
                if buttonTitle == "ς"
                {
                    button.setTitle("ϝ", for: UIControlState())
                }
                else if buttonTitle == "ϝ"
                {
                    button.setTitle("ς", for: UIControlState())
                }
                else
                {
                    if capsLockOn {
                        let text = buttonTitle!.uppercased()
                        button.setTitle("\(text)", for: UIControlState())
                    } else {
                        let text = buttonTitle!.lowercased()
                        button.setTitle("\(text)", for: UIControlState())
                    }
                }
            }
        }
    }
 
    func nextKeyboardPressed(_ button: UIButton) {
        advanceToNextInputMode()
    }
}
