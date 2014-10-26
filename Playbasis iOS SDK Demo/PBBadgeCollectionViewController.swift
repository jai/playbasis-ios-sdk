//
//  PBBadgeCollectionViewController.swift
//  Playbasis iOS SDK Demo
//
//  Created by Jai Govindani on 10/26/14.
//  Copyright (c) 2014 Jai Govindani. All rights reserved.
//

import UIKit

class PBBadgeCollectionViewController : UICollectionViewController, UICollectionViewDataSource, UICollectionViewDelegate, PBResponseHandler {
    
    var badges: [PBBadge]?
    
    override func viewDidLoad() {
        loadBadges()
    }
    
    func loadBadges() {
        Playbasis.sharedInstance().badges(self)
    }
    
    func processResponse(jsonResponse: [NSObject : AnyObject]!, withURL url: NSURL!) {
        badges = PBJSONParser.badgesFromData(jsonResponse)
        collectionView.reloadData()
    }
}
