//
//  ViewController.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 12/24/16.
//  Copyright © 2016 Jeremy March. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//


//see http://norbertlindenberg.com/2015/06/installing-fonts-on-ios/
// to try to install custom font

import UIKit

class ViewController: UIViewController {
    @IBOutlet var textView:UITextView?
    @IBOutlet var installInstructions:UILabel?
    @IBOutlet var titleLabel:UILabel?
    @IBOutlet var settingsButton:UIButton?
    @IBOutlet var installButton:UIButton?
    @IBOutlet var featuresButton:UIButton?
    @IBOutlet var testingButton:UIButton?
    
    var kb:KeyboardViewController? = nil
    
    let embedInContainerApp:Bool = true
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        /*
        let defaults = UserDefaults(suiteName: "group.com.philolog.hoplitekeyboard")
        if defaults != nil
        {
            //defaults?.setValue(UnicodeMode.PreComposedNoPUA.rawValue, forKey: "UnicodeAccents")
            //defaults?.synchronize()
        }
        */
        settingsButton?.addTarget(self, action: #selector(showSettings(button:)), for: .touchUpInside)
        installButton?.addTarget(self, action: #selector(showInstall(button:)), for: .touchUpInside)
        featuresButton?.addTarget(self, action: #selector(showFeatures(button:)), for: .touchUpInside)
        testingButton?.addTarget(self, action: #selector(showTesting(button:)), for: .touchUpInside)
        /*
        let tc:UIColor = UIColor.black
        let bc:UIColor = UIColor.gray
        let orange = UIColor.init(red: 255/255.0, green: 96/255.0, blue: 70/255.0, alpha: 1.0)
        
        settingsButton?.setTitleColor(tc, for: .normal)
        installButton?.setTitleColor(tc, for: .normal)
        featuresButton?.setTitleColor(tc, for: .normal)
        
        settingsButton?.backgroundColor = bc
        installButton?.backgroundColor = bc
        featuresButton?.backgroundColor = bc
 
        let cr:CGFloat = 6.0
        settingsButton?.layer.cornerRadius = cr
        installButton?.layer.cornerRadius = cr
        featuresButton?.layer.cornerRadius = cr
        textView?.layer.cornerRadius = cr
        */
        //these 3 lines prevent undo/redo/paste from displaying above keyboard on ipad
        if #available(iOS 9.0, *)
        {
            let item : UITextInputAssistantItem = textView!.inputAssistantItem
            item.leadingBarButtonGroups = []
            item.trailingBarButtonGroups = []
        }
        NSLog("bounds: \(UIScreen.main.nativeBounds.width )")
        
        //for iphone 5s and narrower
        if UIScreen.main.nativeBounds.width < 641
        {
            titleLabel?.font = UIFont(name: (titleLabel?.font.fontName)!, size: 20.0)
            installInstructions?.font = UIFont(name: (installInstructions?.font.fontName)!, size: 14.0)
        }
 
        if embedInContainerApp
        {
            //textView!.inputView = nil
            //to include keyboard in container app
            kb = KeyboardViewController() //kb needs to be member variable, can't be local to just this function
            kb?.appExt = false
            kb?.topRowButtonDepressNotAppExt = false //prevent top row button expansion in app, to simulate app extension behavior
            textView!.inputView = kb?.view
        }
        
        let a:String = "Try it: \u{03B1}\u{0304}\u{0313}\u{0301}\u{0345}"
        textView?.text = a
        
        //kb?.view.updateConstraints() //heightAnchor.constraint(equalToConstant: (kb?.portraitHeight)!)
        
        //this works to set height
        //k.view.frame = CGRect(x:0 , y:0, width:self.view.frame.width, height:k.portraitHeight)
        
        /*
        //these do not work to set height
         let heightConstraint = NSLayoutConstraint(item: kb?.view!,
         attribute: .height,
         relatedBy: .equal,
         toItem: nil,
         attribute: .notAnAttribute,
         multiplier: 1.0,
         constant: (kb?.portraitHeight)!)
         heightConstraint.priority = 999.0
         heightConstraint.isActive = true
         
         self.inputView!.addConstraint(heightConstraint)
        */
        //these don't work
        //k.view.heightAnchor.constraint(equalToConstant: k.portraitHeight)
        //k.view.widthAnchor.constraint(equalToConstant: self.view.frame.width)
        
        
 
    }
    
    //http://stackoverflow.com/questions/12591192/center-text-vertically-in-a-uitextview
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        
        let tv = object as! UITextView
        var topCorrect:CGFloat  = (tv.bounds.size.height - tv.contentSize.height * tv.zoomScale) / 2.0;
        topCorrect = ( topCorrect < 0.0 ? 0.0 : topCorrect )
        NSLog("content fix")
        tv.contentInset = UIEdgeInsets(top: topCorrect,left: 0,bottom: 0,right: 0)
        
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        //[[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
        self.navigationController?.setNavigationBarHidden(true, animated: true)
        
        //this doesn't work here, but does in hctest?
        //http://stackoverflow.com/questions/12591192/center-text-vertically-in-a-uitextview
        textView?.addObserver(self, forKeyPath: "contentSize", options: [.new], context: nil)
    }

    @objc func showTesting(button: UIButton) {
        
        //TutorialPageViewController *dvc = [self.storyboard instantiateViewControllerWithIdentifier:@"tutorialvc"];
        self.navigationController?.performSegue(withIdentifier: "showTesting", sender: self)
        textView?.resignFirstResponder()
        //[self.navigationController pushViewController:dvc animated:YES];
    }
    
    @objc func showFeatures(button: UIButton) {
        
        //TutorialPageViewController *dvc = [self.storyboard instantiateViewControllerWithIdentifier:@"tutorialvc"];
        self.navigationController?.performSegue(withIdentifier: "showFeatures", sender: self)
        textView?.resignFirstResponder()
        //[self.navigationController pushViewController:dvc animated:YES];
    }
    
    @objc func showInstall(button: UIButton) {
        
        //TutorialPageViewController *dvc = [self.storyboard instantiateViewControllerWithIdentifier:@"tutorialvc"];
        self.navigationController?.performSegue(withIdentifier: "showInstall", sender: self)
        textView?.resignFirstResponder()
        //[self.navigationController pushViewController:dvc animated:YES];
    }
    
    @objc func showSettings(button: UIButton) {
    
    //TutorialPageViewController *dvc = [self.storyboard instantiateViewControllerWithIdentifier:@"tutorialvc"];
        self.navigationController?.performSegue(withIdentifier: "showSettings", sender: self)
        textView?.resignFirstResponder()
        
    //[self.navigationController pushViewController:dvc animated:YES];
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}
