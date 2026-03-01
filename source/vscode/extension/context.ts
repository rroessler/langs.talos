/// Vendor Modules
import * as vscode from 'vscode';

/// Talos Modules
import { Dependency } from '@/talos/utilities';

/** Extension Service API. */
export const Context = Dependency.Name('extension.context');
export interface Context extends vscode.ExtensionContext {}
