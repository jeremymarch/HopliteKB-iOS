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
let orange = UIColor.init(red: 255/255.0, green: 96/255.0, blue: 70/255.0, alpha: 1.0)
let green = UIColor.init(red: 102/255.0, green: 200/255.0, blue: 255/255.0, alpha: 1.0)
let darkBlue = UIColor.init(red: 50/255.0, green: 90/255.0, blue: 139/255.0, alpha: 1.0)

public struct HopliteConstants{
    
    static let enterBGColor = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
    static let enterTextColor = UIColor.white
    static let enterBGColorDown = UIColor.white
    static let enterTextColorDown = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
    
    static let keyBGColor = UIColor.white
    static let keyTextColor = UIColor.black
    static let keyBGColorDown = UIColor.black
    static let keyTextColorDown = UIColor.white
    
    static let accentBGColor = orange//UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let accentTextColor = UIColor.black
    static let accentBGColorDown = UIColor.black
    static let accentTextColorDown = UIColor.white
    
    static let punctuationBGColor = darkBlue// green//UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let punctuationTextColor = UIColor.white
    static let punctuationBGColorDown = green
    static let punctuationTextColorDown = UIColor.black
    
    static let deleteBGColor = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let deleteInnerColor = UIColor.init(red: 229/255.0, green: 230/255.0, blue: 233/255.0, alpha: 1.0)
    static let deleteXColor = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let deleteBGColorDown = UIColor.white
    static let deleteInnerColorDown = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let deleteXColorDown = UIColor.init(red: 229/255.0, green: 230/255.0, blue: 233/255.0, alpha: 1.0)

    //capslock, globe, backspace
    static let otherBGColor = UIColor.lightGray
    static let otherTextColor = UIColor.black
    static let otherBGColorDown = UIColor.black
    static let otherTextColorDown = UIColor.white
    static let normalRadius:CGFloat = 4.0
    static let ipadRadius:CGFloat = 6.0
}

public struct HopliteConstants1{
    static let constX=1;
    
    static let enterBGColor = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
    static let enterTextColor = UIColor.white
    static let enterBGColorDown = UIColor.white
    static let enterTextColorDown = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
    
    static let keyBGColor = UIColor.white
    static let keyTextColor = UIColor.black
    static let keyBGColorDown = UIColor.black
    static let keyTextColorDown = UIColor.white
    
    static let accentBGColor = UIColor.init(red: 0/255.0, green: 150.0/255.0, blue: 70/255.0, alpha: 1.0)
    static let accentTextColor = UIColor.white
    static let accentBGColorDown = UIColor.black
    static let accentTextColorDown = UIColor.white
    
    static let punctuationBGColor = UIColor.orange
    static let punctuationTextColor = UIColor.black
    static let punctuationBGColorDown = UIColor.black
    static let punctuationTextColorDown = UIColor.white
    
    //capslock, globe, backspace
    static let otherKeyBGColor = UIColor.white
    static let otherKeyTextColor = UIColor.black
    static let otherKeyBGColorDown = UIColor.black
    static let otherKeyTextColorDown = UIColor.white
    
    static let deleteBGColor = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let deleteInnerColor = UIColor.init(red: 229/255.0, green: 230/255.0, blue: 233/255.0, alpha: 1.0)
    static let deleteXColor = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let deleteBGColorDown = UIColor.white
    static let deleteInnerColorDown = UIColor.init(red: 110/255.0, green: 110/255.0, blue: 128/255.0, alpha: 1.0)
    static let deleteXColorDown = UIColor.init(red: 229/255.0, green: 230/255.0, blue: 233/255.0, alpha: 1.0)
}

class KeyboardViewController: UIInputViewController {

    var capsLockOn:Bool = false
    let bgColor = UIColor.init(red: 200/255.0, green: 200/255.0, blue: 200/255.0, alpha: 1.0)
    let keyTextColor = UIColor.black
    let useAnimation:Bool = false
    var deleteHoldTimer:Timer? = nil
    let stackView1   = UIStackView()
    let stackView2   = UIStackView()
    let stackView3   = UIStackView()
    let stackView4   = UIStackView()
    var tic:Int = 0
    
    var deleteButton:UIButton? = nil
    var globeButton:UIButton? = nil
    var capsLockButton:UIButton? = nil
    var periodButton:UIButton? = nil
    
    var heightConstraint:NSLayoutConstraint?
    
    let fontSize:CGFloat = 24.0
    let smallerFontSize:CGFloat = 20.0

    var portraitHeight:CGFloat = 240.0
    var landscapeHeight:CGFloat = 190.0
    
    let buttonHeightMultiplier:CGFloat = 0.174
    let buttonSpacing:CGFloat = 5.0
    let widthMultiple:CGFloat = 0.0976
    
    var currentButton:UIButton?
    //let widthMultiple2:CGFloat = 1/10
    
    /*
     //best to update constraint in place rather than in updateConstraints() if possible, see:
     //https://developer.apple.com/reference/uikit/uiviewcontroller/1621379-updateviewconstraints
    override func updateViewConstraints() {
        // Add custom view sizing constraints here
        if (self.view.frame.size.width == 0 || self.view.frame.size.height == 0) {
            return
        }
        //self.inputView!.removeConstraint(heightConstraint!)
        let screenSize = UIScreen.main.bounds.size
        let screenH = screenSize.height;
        let screenW = screenSize.width;
        let isLandscape =  !(self.view.frame.size.width == screenW * ((screenW < screenH) ? 1 : 0) + screenH * ((screenW > screenH) ? 1 : 0))
        
        //NSLog(isLandscape ? "Screen: Landscape" : "Screen: Potrait");
        if (isLandscape) {
            heightConstraint!.constant = landscapeHeight;
            //self.inputView!.addConstraint(heightConstraint!)
        } else {
            heightConstraint!.constant = self.portraitHeight;
            //self.inputView!.addConstraint(heightConstraint!)
        }
        super.updateViewConstraints()
    }
    */
    /*
     //http://stackoverflow.com/questions/31916979/how-touch-drag-enter-works
    func handleDrag(gestureRecognizer:UIPanGestureRecognizer)
    {
        let point:CGPoint  = gestureRecognizer.location(in: self.view)
        let draggedView = self.view.hitTest(point, with: nil)! as! UIButton
        
        if gestureRecognizer.state == .changed
        {
            if draggedView is UIButton && self.currentButton == nil {
                self.currentButton = draggedView
                NSLog("Enter: \(self.currentButton?.tag)")
                
                // send enter event to your button
                self.currentButton?.sendActions(for: .touchDragEnter)
            }
            
            if self.currentButton != nil && !(self.currentButton?.isEqual(draggedView))!
            {
                NSLog("Out: \(self.currentButton?.tag)")
                
                // send exit event to your button
                self.currentButton?.sendActions(for: .touchDragExit)
                self.currentButton = nil;
            }
        }
        else if (gestureRecognizer.state == .ended)
        {
            self.currentButton = nil
        }
    }
    */
    override func viewWillLayoutSubviews() {
        super.viewWillLayoutSubviews()
        // Update height when rotates
        //updateViewConstraints()
        //self.inputView!.setNeedsUpdateConstraints()
        
        globeButton?.setNeedsDisplay() //to redraw globe icon
        capsLockButton?.setNeedsDisplay()
        deleteButton?.setNeedsDisplay()
        
        //these fix a problem where buttons are not initially drawn correctly?
        stackView2.arrangedSubviews.forEach {view in
            view.setNeedsDisplay()
        }
        stackView3.arrangedSubviews.forEach {view in
            view.setNeedsDisplay()
        }
        stackView4.arrangedSubviews.forEach {view in
            view.setNeedsDisplay()
        }
    }
 
    //http://stackoverflow.com/questions/26069874/what-is-the-right-way-to-handle-orientation-changes-in-ios-8
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        super.viewWillTransition(to: size, with: coordinator)
        coordinator.animate(alongsideTransition: { _ in
            
            if self.view.frame.size.width != 0 && self.view.frame.size.height != 0
            {
                //self.inputView!.removeConstraint(self.heightConstraint!)
                let screenSize = UIScreen.main.bounds.size
                let screenH = screenSize.height
                let screenW = screenSize.width
                let isLandscape =  !(self.view.frame.size.width == screenW * ((screenW < screenH) ? 1 : 0) + screenH * ((screenW > screenH) ? 1 : 0))
                
                //NSLog(isLandscape ? "Screen: Landscape" : "Screen: Potrait");
                if (isLandscape) {
                    self.heightConstraint!.constant = self.landscapeHeight;
                    //self.inputView!.addConstraint(self.heightConstraint!)
                } else {
                    self.heightConstraint!.constant = self.portraitHeight;
                    //self.inputView!.addConstraint(self.heightConstraint!)
                }
                
                self.globeButton?.setNeedsDisplay() //to redraw globe icon
                self.capsLockButton?.setNeedsDisplay()
                self.deleteButton?.setNeedsDisplay()
            }
        
        }, completion: nil)
    }
 
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
        NSLog("keyboard did load111")
        if UIDevice.current.userInterfaceIdiom == .pad
        {
            portraitHeight = 350.0
            landscapeHeight = 310.0
        }
        else
        {
            portraitHeight = 240.0
            landscapeHeight = 190.0
        }
        
        //NSLog("kb view did load")
        self.view.translatesAutoresizingMaskIntoConstraints = true //this is needed
        self.view.isUserInteractionEnabled = true
        self.view.backgroundColor = bgColor

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
        
        stackView1.translatesAutoresizingMaskIntoConstraints = false
        stackView2.translatesAutoresizingMaskIntoConstraints = false
        stackView3.translatesAutoresizingMaskIntoConstraints = false
        stackView4.translatesAutoresizingMaskIntoConstraints = false
        stackView5.translatesAutoresizingMaskIntoConstraints = false
        stackViewV.translatesAutoresizingMaskIntoConstraints = false
        
        stackViewV.addArrangedSubview(stackView1)
        stackViewV.addArrangedSubview(stackView2)
        stackViewV.addArrangedSubview(stackView3)
        stackViewV.addArrangedSubview(stackView4)
        stackViewV.addArrangedSubview(stackView5)
        
        self.view.addSubview(stackViewV)
        
        stackViewV.rightAnchor.constraint(equalTo: self.view.rightAnchor).isActive = true
        stackViewV.leftAnchor.constraint(equalTo: self.view.leftAnchor).isActive = true
        stackViewV.topAnchor.constraint(equalTo: self.view.topAnchor, constant:buttonSpacing).isActive = true
        stackViewV.bottomAnchor.constraint(equalTo: self.view.bottomAnchor, constant:-buttonSpacing).isActive = true
        
        
        //herehere
        //set whole keyboard height
        //http://stackoverflow.com/questions/24167909/ios-8-custom-keyboard-changing-the-height
        //self.view.heightAnchor.constraint(equalToConstant: <#T##CGFloat#>)
        
        //self.inputView?.heightAnchor.constraint(equalToConstant: 236.0).isActive = true
        
        heightConstraint = NSLayoutConstraint(item: self.inputView!,
                                              attribute: .height,
                                              relatedBy: .equal,
                                              toItem: nil,
                                              attribute: .notAnAttribute,
                                              multiplier: 1.0,
                                              constant: portraitHeight)
        heightConstraint!.priority = 999.0
        heightConstraint?.isActive = true
        
        //self.inputView!.addConstraint(heightConstraint!)
        
        /*
            punctuation:
            period
            comma
            raised dot (ano teleia)
            question mark
            parentheses
        */
        let keys: [[String]] = [["῾", "᾿", "´", "`", "˜", "¯", "ͺ", ",","·"],
                                ["ε", "ρ", "τ", "υ", "θ", "ι", "ο", "π"],
                               ["α", "σ", "δ", "φ", "γ", "η", "ξ", "κ", "λ"],
                               ["ζ", "χ", "ψ", "ω", "β", "ν", "μ", "ς", "BK" ],
                               ["CP", "KB", "space", ".", "enter"]]
        
        for row in keys
        {
            for key in row
            {
                var b:UIButton

                if row == keys[0]
                {
                    if key == "·" || key == ","
                    {
                        b = HCPunctuationButton(buttonType:1)
                    }
                    else
                    {
                        b = HCAccentButton(buttonType:1)
                    }
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    if UIDevice.current.userInterfaceIdiom == .pad
                    {
                        b.layer.cornerRadius = HopliteConstants.ipadRadius
                    }
                    else
                    {
                        b.layer.cornerRadius = HopliteConstants.normalRadius
                    }
                    //b.titleLabel?.textColor = UIColor.black
                    //b.setTitleColor(keyTextColor, for: [])
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
                        b.titleEdgeInsets = UIEdgeInsetsMake(-30, 0, 0, 0)
                        b.addTarget(self, action: #selector(accentPressed(_:)), for: .touchUpInside)
                    }
                    else if key == ";"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    }
                    else if key == ","
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
                    else if key == "("
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    }
                    else if key == ")"
                    {
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.titleEdgeInsets = UIEdgeInsetsMake(20, 0, 0, 0)
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    }
                    
                    stackView1.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                    b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                }
                else if row == keys[1]
                {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    //b.layer.cornerRadius = 4.0
                    //b.titleLabel?.textColor = UIColor.black
                    //b.setTitleColor(keyTextColor, for: [])
                    //b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    //b.addTarget(self, action: #selector(self.keyPressedDown(button:)), for: .touchDown)
                    stackView2.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                    b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                }
                else if row == keys[2]
                {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    //b.layer.cornerRadius = 4.0
                    //b.titleLabel?.textColor = UIColor.black
                    b.setTitleColor(keyTextColor, for: [])
                    b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    stackView3.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                    b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                }
                else if row == keys[3]
                {
                    if key == "BK"
                    {
                        b = HCDeleteButton(devicea:2)
                        
                        let lpgr = UILongPressGestureRecognizer(target: self, action: #selector(longDeletePressGesture))
                        lpgr.minimumPressDuration = 0.4
                        lpgr.delaysTouchesBegan = false //needed so it also listens for touchdown
                        lpgr.allowableMovement = 50.0
                        b.addGestureRecognizer(lpgr)
                        
                        //need both long and normal
                        b.addTarget(self, action: #selector(backSpacePressed(_:)), for: .touchDown)
                        stackView4.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: (widthMultiple * 1)).isActive = true
                        b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                        
                        deleteButton = b
                    }
                    else
                    {
                    b = HCButton(buttonType:1)
                    
                    //b.layer.borderWidth = 1.0
                    //b.layer.borderColor = UIColor.blue.cgColor
                    //b.layer.cornerRadius = 4.0
                    //b.titleLabel?.textColor = UIColor.black
                    b.setTitleColor(keyTextColor, for: [])
                    b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                    //b.layer.backgroundColor = UIColor.brown.cgColor
                    b.setTitle(key, for: [])
                    
                    b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                    stackView4.addArrangedSubview(b)
                    b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                    b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                    }
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
                        if UIDevice.current.userInterfaceIdiom == .pad
                        {
                            b.layer.cornerRadius = HopliteConstants.ipadRadius
                        }
                        else
                        {
                            b.layer.cornerRadius = HopliteConstants.normalRadius
                        }
                        b.titleLabel?.textColor = UIColor.black
                        b.setTitleColor(keyTextColor, for: [])
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.layer.backgroundColor = UIColor.brown.cgColor
                        b.setTitle("", for: [])
                        
                        b.addTarget(self, action: #selector(capsPressed(_:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                        b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                        
                        capsLockButton = b
                    }
                    else if key == "KB"
                    {
                        b = HCGlobeButton()
                        
                        //b.layer.borderWidth = 1.0
                        //b.layer.borderColor = UIColor.blue.cgColor
                        if UIDevice.current.userInterfaceIdiom == .pad
                        {
                            b.layer.cornerRadius = HopliteConstants.ipadRadius
                        }
                        else
                        {
                            b.layer.cornerRadius = HopliteConstants.normalRadius
                        }
                        b.titleLabel?.textColor = UIColor.black
                        b.setTitleColor(keyTextColor, for: [])
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        //b.layer.backgroundColor = UIColor.brown.cgColor
                        b.setTitle("", for: [])
                        
                        //b.setTitle("", for: [])
                        //b.addTarget(self, action: #selector(handleInputModeList(from:with:)), for: .touchUpInside)
                        b.addTarget(self, action: #selector(nextKeyboardPressed(_:)), for: .touchUpInside)
                        
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                        b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                        
                        globeButton = b
                    }
                    else if key == "enter"
                    {
                        b = HCEnterButton()
                        
                        b.addTarget(self, action: #selector(returnPressed(_:)), for: .touchUpInside)
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: smallerFontSize)
                        stackView5.addArrangedSubview(b)
                        if UIDevice.current.userInterfaceIdiom == .pad
                        {
                            b.layer.cornerRadius = HopliteConstants.ipadRadius
                        }
                        else
                        {
                            b.layer.cornerRadius = HopliteConstants.normalRadius
                        }
                        b.setTitle(key, for: [])
                        b.setTitleColor(UIColor.white, for: [])

                        b.backgroundColor = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
                        
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: (widthMultiple * 2.5)).isActive = true
                        b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                    }
                    else if key == "space"
                    {
                        b = HCSpaceButton()
                        if UIDevice.current.userInterfaceIdiom == .pad
                        {
                            b.layer.cornerRadius = HopliteConstants.ipadRadius
                        }
                        else
                        {
                            b.layer.cornerRadius = HopliteConstants.normalRadius
                        }
                        b.setTitleColor(UIColor.gray, for: [])
                        b.setTitle(key, for: [])
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: smallerFontSize)
                        //b.layer.borderColor = UIColor.gray.cgColor
                        b.addTarget(self, action: #selector(spacePressed(_:)), for: .touchUpInside)
                        //b.addTarget(self, action: #selector(didDoubleTapSapce(_:)), for: .touchDownRepeat)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: (widthMultiple * 3)).isActive = true
                        b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                    }
                    else if key == "."
                    {
                        b = HCPunctuationButton(buttonType:1)
                        if UIDevice.current.userInterfaceIdiom == .pad
                        {
                            b.layer.cornerRadius = HopliteConstants.ipadRadius
                        }
                        else
                        {
                            b.layer.cornerRadius = HopliteConstants.normalRadius
                        }
                        b.titleLabel!.font = UIFont(name: b.titleLabel!.font.fontName, size: fontSize)
                        b.setTitle(key, for: [])
                        
                        b.addTarget(self, action: #selector(self.keyPressed(button:)), for: .touchUpInside)
                        stackView5.addArrangedSubview(b)
                        b.widthAnchor.constraint(equalTo: stackViewV.widthAnchor, multiplier: widthMultiple).isActive = true
                        b.heightAnchor.constraint(equalTo: stackViewV.heightAnchor, multiplier: buttonHeightMultiplier).isActive = true
                        
                        periodButton = b
                    }

                }
            }
        }
        
        //Timer.scheduledTimer(timeInterval: 0.5, target: self, selector: #selector(self.runDemo(_:)), userInfo: nil, repeats: true)
        
    }

    //DEMO
    func runDemo(_ timer: Timer)
    {
        switch self.tic {
        case 0:
            let a:UIButton = stackView3.arrangedSubviews[0] as! UIButton //ALPHA
            a.sendActions(for: .touchDown)
        case 1:
            let a:UIButton = stackView3.arrangedSubviews[0] as! UIButton
            a.sendActions(for: .touchUpInside)
        case 2:
            let a:UIButton = stackView1.arrangedSubviews[5] as! UIButton //MACRON
            a.sendActions(for: .touchDown)
        case 3:
            let a:UIButton = stackView1.arrangedSubviews[5] as! UIButton
            a.sendActions(for: .touchUpInside)
        case 4:
            let a:UIButton = stackView1.arrangedSubviews[1] as! UIButton //SMOOTH
            a.sendActions(for: .touchDown)
        case 5:
            let a:UIButton = stackView1.arrangedSubviews[1] as! UIButton
            a.sendActions(for: .touchUpInside)
        case 6:
            let a:UIButton = stackView1.arrangedSubviews[2] as! UIButton //ACUTE
            a.sendActions(for: .touchDown)
        case 7:
            let a:UIButton = stackView1.arrangedSubviews[2] as! UIButton
            a.sendActions(for: .touchUpInside)
        case 8:
            let a:UIButton = stackView1.arrangedSubviews[6] as! UIButton //IOTA SUB
            a.sendActions(for: .touchDown)
        case 9:
            let a:UIButton = stackView1.arrangedSubviews[6] as! UIButton
            a.sendActions(for: .touchUpInside)
        default: break
        }
        self.tic += 1
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
        
        var textColor:UIColor?
        let proxy = self.textDocumentProxy
        if proxy.keyboardAppearance == UIKeyboardAppearance.dark {
            textColor = UIColor.white
        } else {
            textColor = UIColor.black
        }
        globeButton!.setTitleColor(textColor, for: [])
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
/*
    func keyPressedDown(button: UIButton) {
        //button.superview!.bringSubview(toFront: button)
    }
    */
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
        if capsLockOn
        {
            periodButton?.setTitle(";", for: UIControlState())
        }
        else
        {
            periodButton?.setTitle(".", for: UIControlState())
        }
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
                else if buttonTitle == nil || buttonTitle == ""
                {
                    //delete button
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
