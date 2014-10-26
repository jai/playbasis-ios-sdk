//
//  ViewController.swift
//  Playbasis iOS SDK Demo
//
//  Created by Jai Govindani on 10/21/14.
//  Copyright (c) 2014 Jai Govindani. All rights reserved.
//

import UIKit

class ViewController: UIViewController, PBResponseHandler {

    var pb: Playbasis
    @IBOutlet weak var responseTextView: UITextView?
    @IBOutlet weak var authorizationStatusLabel: UILabel?

    required init(coder aDecoder: NSCoder) {
        
        //Init the playbasis SDK client
        pb = Playbasis.sharedInstance()
        super.init(coder: aDecoder)
        
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        if let currentToken = NSUserDefaults.standardUserDefaults().stringForKey("token") {
            //Authorized
            
            //Need to auth again anyways because the SDK client doesn't save its API key
            pb.auth("1470525946", "a25b2433d41c4a2100daac50ddffc498", self)
            setAuthorizationStatus(true)
        } else {
            setAuthorizationStatus(false)
            pb.auth("1470525946", "a25b2433d41c4a2100daac50ddffc498", self)
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func processResponse(jsonResponse: [NSObject : AnyObject]!, withURL url: NSURL!) {
        var currentText = (responseTextView != nil) ? responseTextView?.text : ""
        
        //Force unwrap because currentText could be nil since responseTextView could be nil
        if countElements(currentText!) > 0 {
            currentText = currentText! + "\n" + jsonResponse.description
        } else {
            currentText = jsonResponse.description
        }
        
        responseTextView?.text = currentText
        
        if url.absoluteString!.rangeOfString("Auth") != nil {
            //Auth request
            responseTextView?.text = "authorized!"
            
            let responseDictionary = jsonResponse as Dictionary<String, AnyObject>
            if let responseTokenInfo = responseDictionary["response"] as? Dictionary<String, AnyObject> {
                let token = responseTokenInfo["token"] as String
                let tokenExpirationDate = responseTokenInfo["date_expire"] as String
                
                NSUserDefaults.standardUserDefaults().setObject(token, forKey: "token")
                NSUserDefaults.standardUserDefaults().setObject(tokenExpirationDate, forKey: "tokenExpirationDate")
                setAuthorizationStatus(true)
            }
        }
    }
    
    func setAuthorizationStatus(authorizationStatus: Bool) {
        if authorizationStatus {
            authorizationStatusLabel?.backgroundColor = UIColor(red:46/255.0, green:204/255.0, blue:113/255.0, alpha:1.0)
            authorizationStatusLabel?.textColor = UIColor.whiteColor()
            authorizationStatusLabel?.text = "Connection to Playbasis authorized"
        } else {
            authorizationStatusLabel?.backgroundColor = UIColor(red:231/255.0, green:76/255.0, blue:60/255.0, alpha:1.0)
            authorizationStatusLabel?.textColor = UIColor.whiteColor()
            authorizationStatusLabel?.text = NSLocalizedString("Unauthorized!", comment:"Unauthorized!")
        }
    }

}

